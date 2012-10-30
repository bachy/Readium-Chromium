// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// MSVC++ requires this to get M_PI.
#define _USE_MATH_DEFINES
#include <math.h>

#include "remoting/codec/audio_encoder_opus.h"

#include "base/logging.h"
#include "remoting/codec/audio_decoder_opus.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace remoting {

namespace {

// Maximum value that can be encoded in a 16-bit signed sample.
const int kMaxSampleValue = 32767;

const int kChannels = 2;

// Phase shift between left and right channels.
const double kChannelPhaseShift = 2 * M_PI / 3;

// The sampling rate that OPUS uses internally and that we expect to get
// from the decoder.
const AudioPacket_SamplingRate kDefaultSamplingRate =
    AudioPacket::SAMPLING_RATE_48000;

// Maximum latency expected from the encoder.
const int kMaxLatencyMs = 40;

// When verifying results ignore the first 1k samples. This is necessary because
// it takes some time for the codec to adjust for the input signal.
const int kSkippedFirstSamples = 1000;

// Maximum standard deviation of the difference between original and decoded
// signals as a proportion of kMaxSampleValue. For two unrelated signals this
// difference will be close to 1.0, even for signals that differ only slightly.
// The value is chosen such that all the tests pass normally, but fail with
// small changes (e.g. one sample shift between signals).
const double kMaxSignalDeviation = 0.1;

}  // namespace

class OpusAudioEncoderTest : public testing::Test {
 public:
  // Return test signal value at the specified position |pos|. |frequency_hz|
  // defines frequency of the signal. |channel| is used to calculate phase shift
  // of the signal, so that different signals are generated for left and right
  // channels.
  static int16 GetSampleValue(
      AudioPacket::SamplingRate rate,
      double frequency_hz,
      double pos,
      int channel) {
    double angle = pos * 2 * M_PI * frequency_hz / rate +
        kChannelPhaseShift * channel;
    return static_cast<int>(sin(angle) * kMaxSampleValue + 0.5);
  }

  // Creates  audio packet filled with a test signal with the specified
  // |frequency_hz|.
  scoped_ptr<AudioPacket> CreatePacket(
      int samples,
      AudioPacket::SamplingRate rate,
      double frequency_hz,
      int pos) {
    std::vector<int16> data(samples * kChannels);
    for (int i = 0; i < samples; ++i) {
      data[i * kChannels] = GetSampleValue(rate, frequency_hz, i + pos, 0);
      data[i * kChannels + 1] = GetSampleValue(rate, frequency_hz, i + pos, 1);
    }

    scoped_ptr<AudioPacket> packet(new AudioPacket());
    packet->add_data(reinterpret_cast<char*>(&(data[0])),
                     samples * kChannels * sizeof(int16));
    packet->set_encoding(AudioPacket::ENCODING_RAW);
    packet->set_sampling_rate(rate);
    packet->set_bytes_per_sample(AudioPacket::BYTES_PER_SAMPLE_2);
    packet->set_channels(AudioPacket::CHANNELS_STEREO);
    return packet.Pass();
  }

  // Decoded data is normally shifted in phase relative to the original signal.
  // This function returns the approximate shift in samples by finding the first
  // point when signal goes from negative to positive.
  double EstimateSignalShift(const std::vector<int16>& received_data) {
    for (size_t i = kSkippedFirstSamples;
         i < received_data.size() / kChannels - 1; i++) {
      int16 this_sample = received_data[i * kChannels];
      int16 next_sample = received_data[(i + 1) * kChannels];
      if (this_sample < 0 && next_sample > 0) {
        return
            i + static_cast<double>(-this_sample) / (next_sample - this_sample);
      }
    }
    return 0;
  }

  // Compares decoded signal with the test signal that was encoded. It estimates
  // phase shift from the original signal, then calculates standard deviation of
  // the difference between original and decoded signals.
  void ValidateReceivedData(int samples,
                            AudioPacket::SamplingRate rate,
                            double frequency_hz,
                            const std::vector<int16>& received_data) {
    double shift = EstimateSignalShift(received_data);
    double diff_sqare_sum = 0;
    for (size_t i = kSkippedFirstSamples;
         i < received_data.size() / kChannels; i++) {
      double d = received_data[i * kChannels] -
          GetSampleValue(rate, frequency_hz, i - shift, 0);
      diff_sqare_sum += d * d;
      d = received_data[i * kChannels + 1] -
          GetSampleValue(rate, frequency_hz, i - shift, 1);
      diff_sqare_sum += d * d;
    }
    double deviation = sqrt(diff_sqare_sum / received_data.size())
         / kMaxSampleValue;
    EXPECT_LE(deviation, kMaxSignalDeviation);
  }

  void TestEncodeDecode(int packet_size,
                          double frequency_hz,
                          AudioPacket::SamplingRate rate) {
    const int kTotalTestSamples = 24000;

    encoder_.reset(new AudioEncoderOpus());
    decoder_.reset(new AudioDecoderOpus());

    std::vector<int16> received_data;
    int pos = 0;
    for (; pos < kTotalTestSamples; pos += packet_size) {
        scoped_ptr<AudioPacket> source_packet =
            CreatePacket(packet_size, rate, frequency_hz, pos);
        scoped_ptr<AudioPacket> encoded =
            encoder_->Encode(source_packet.Pass());
        if (encoded.get()) {
          scoped_ptr<AudioPacket> decoded = decoder_->Decode(encoded.Pass());
          EXPECT_EQ(kDefaultSamplingRate, decoded->sampling_rate());
          for (int i = 0; i < decoded->data_size(); ++i) {
            const int16* data =
                reinterpret_cast<const int16*>(decoded->data(i).data());
            received_data.insert(
                received_data.end(), data,
                data + decoded->data(i).size() / sizeof(int16));
          }
        }
    }

    // Verify that at most kMaxLatencyMs worth of samples is buffered inside
    // |encoder_| and |decoder_|.
    EXPECT_GE(static_cast<int>(received_data.size()) / kChannels,
              pos - rate * kMaxLatencyMs / 1000);

    ValidateReceivedData(packet_size, kDefaultSamplingRate,
                         frequency_hz, received_data);
  }

 protected:
  scoped_ptr<AudioEncoderOpus> encoder_;
  scoped_ptr<AudioDecoderOpus> decoder_;
};

TEST_F(OpusAudioEncoderTest, CreateAndDestroy) {
}

TEST_F(OpusAudioEncoderTest, NoResampling) {
  TestEncodeDecode(2000, 50, AudioPacket::SAMPLING_RATE_48000);
  TestEncodeDecode(2000, 3000, AudioPacket::SAMPLING_RATE_48000);
  TestEncodeDecode(2000, 10000, AudioPacket::SAMPLING_RATE_48000);
}

TEST_F(OpusAudioEncoderTest, Resampling) {
  TestEncodeDecode(2000, 50, AudioPacket::SAMPLING_RATE_44100);
  TestEncodeDecode(2000, 3000, AudioPacket::SAMPLING_RATE_44100);
  TestEncodeDecode(2000, 10000, AudioPacket::SAMPLING_RATE_44100);
}

TEST_F(OpusAudioEncoderTest, BufferSizeAndResampling) {
  TestEncodeDecode(500, 3000, AudioPacket::SAMPLING_RATE_44100);
  TestEncodeDecode(1000, 3000, AudioPacket::SAMPLING_RATE_44100);
  TestEncodeDecode(5000, 3000, AudioPacket::SAMPLING_RATE_44100);
}

}  // namespace remoting
