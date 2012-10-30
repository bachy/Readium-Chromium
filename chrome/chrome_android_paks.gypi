# Copyright (c) 2012 The Chromium Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.
{
  'variables': {
    'chrome_android_pak_output_folder': '<@(PRODUCT_DIR)/../assets/chrome',
    'chrome_android_pak_input_resources': [
      '<(PRODUCT_DIR)/chrome.pak',
      '<(PRODUCT_DIR)/resources.pak',
      '<(PRODUCT_DIR)/chrome_100_percent.pak',
      '<(PRODUCT_DIR)/locales/ar.pak',
      '<(PRODUCT_DIR)/locales/bg.pak',
      '<(PRODUCT_DIR)/locales/ca.pak',
      '<(PRODUCT_DIR)/locales/cs.pak',
      '<(PRODUCT_DIR)/locales/da.pak',
      '<(PRODUCT_DIR)/locales/de.pak',
      '<(PRODUCT_DIR)/locales/el.pak',
      '<(PRODUCT_DIR)/locales/en-GB.pak',
      '<(PRODUCT_DIR)/locales/en-US.pak',
      '<(PRODUCT_DIR)/locales/es.pak',
      '<(PRODUCT_DIR)/locales/es-419.pak',
      '<(PRODUCT_DIR)/locales/fa.pak',
      '<(PRODUCT_DIR)/locales/fi.pak',
      '<(PRODUCT_DIR)/locales/fil.pak',
      '<(PRODUCT_DIR)/locales/fr.pak',
      '<(PRODUCT_DIR)/locales/he.pak',
      '<(PRODUCT_DIR)/locales/hi.pak',
      '<(PRODUCT_DIR)/locales/hr.pak',
      '<(PRODUCT_DIR)/locales/hu.pak',
      '<(PRODUCT_DIR)/locales/id.pak',
      '<(PRODUCT_DIR)/locales/it.pak',
      '<(PRODUCT_DIR)/locales/ja.pak',
      '<(PRODUCT_DIR)/locales/ko.pak',
      '<(PRODUCT_DIR)/locales/lt.pak',
      '<(PRODUCT_DIR)/locales/lv.pak',
      '<(PRODUCT_DIR)/locales/nb.pak',
      '<(PRODUCT_DIR)/locales/nl.pak',
      '<(PRODUCT_DIR)/locales/pl.pak',
      '<(PRODUCT_DIR)/locales/pt-BR.pak',
      '<(PRODUCT_DIR)/locales/pt-PT.pak',
      '<(PRODUCT_DIR)/locales/ro.pak',
      '<(PRODUCT_DIR)/locales/ru.pak',
      '<(PRODUCT_DIR)/locales/sk.pak',
      '<(PRODUCT_DIR)/locales/sl.pak',
      '<(PRODUCT_DIR)/locales/sr.pak',
      '<(PRODUCT_DIR)/locales/sv.pak',
      '<(PRODUCT_DIR)/locales/th.pak',
      '<(PRODUCT_DIR)/locales/tr.pak',
      '<(PRODUCT_DIR)/locales/uk.pak',
      '<(PRODUCT_DIR)/locales/vi.pak',
      '<(PRODUCT_DIR)/locales/zh-CN.pak',
      '<(PRODUCT_DIR)/locales/zh-TW.pak',
    ],
    'chrome_android_pak_output_resources': [
      '<(chrome_android_pak_output_folder)/chrome.pak',
      '<(chrome_android_pak_output_folder)/resources.pak',
      '<(chrome_android_pak_output_folder)/chrome_100_percent.pak',
      '<(chrome_android_pak_output_folder)/ar.pak',
      '<(chrome_android_pak_output_folder)/bg.pak',
      '<(chrome_android_pak_output_folder)/ca.pak',
      '<(chrome_android_pak_output_folder)/cs.pak',
      '<(chrome_android_pak_output_folder)/da.pak',
      '<(chrome_android_pak_output_folder)/de.pak',
      '<(chrome_android_pak_output_folder)/el.pak',
      '<(chrome_android_pak_output_folder)/en-GB.pak',
      '<(chrome_android_pak_output_folder)/en-US.pak',
      '<(chrome_android_pak_output_folder)/es.pak',
      '<(chrome_android_pak_output_folder)/es-419.pak',
      '<(chrome_android_pak_output_folder)/fa.pak',
      '<(chrome_android_pak_output_folder)/fi.pak',
      '<(chrome_android_pak_output_folder)/fil.pak',
      '<(chrome_android_pak_output_folder)/fr.pak',
      '<(chrome_android_pak_output_folder)/he.pak',
      '<(chrome_android_pak_output_folder)/hi.pak',
      '<(chrome_android_pak_output_folder)/hr.pak',
      '<(chrome_android_pak_output_folder)/hu.pak',
      '<(chrome_android_pak_output_folder)/id.pak',
      '<(chrome_android_pak_output_folder)/it.pak',
      '<(chrome_android_pak_output_folder)/ja.pak',
      '<(chrome_android_pak_output_folder)/ko.pak',
      '<(chrome_android_pak_output_folder)/lt.pak',
      '<(chrome_android_pak_output_folder)/lv.pak',
      '<(chrome_android_pak_output_folder)/nb.pak',
      '<(chrome_android_pak_output_folder)/nl.pak',
      '<(chrome_android_pak_output_folder)/pl.pak',
      '<(chrome_android_pak_output_folder)/pt-BR.pak',
      '<(chrome_android_pak_output_folder)/pt-PT.pak',
      '<(chrome_android_pak_output_folder)/ro.pak',
      '<(chrome_android_pak_output_folder)/ru.pak',
      '<(chrome_android_pak_output_folder)/sk.pak',
      '<(chrome_android_pak_output_folder)/sl.pak',
      '<(chrome_android_pak_output_folder)/sr.pak',
      '<(chrome_android_pak_output_folder)/sv.pak',
      '<(chrome_android_pak_output_folder)/th.pak',
      '<(chrome_android_pak_output_folder)/tr.pak',
      '<(chrome_android_pak_output_folder)/uk.pak',
      '<(chrome_android_pak_output_folder)/vi.pak',
      '<(chrome_android_pak_output_folder)/zh-CN.pak',
      '<(chrome_android_pak_output_folder)/zh-TW.pak',
    ],
  },
}

