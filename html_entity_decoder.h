//          Copyright Rich Elmes 2019
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

/*******************************************************************************
 The block below describes the properties of this module, and is read by
 the Projucer to automatically generate project code that uses it.
 For details about the syntax and how to create or use a module, see the
 JUCE Module Format.txt file.


 BEGIN_JUCE_MODULE_DECLARATION

  ID:               html_entity_decoder
  vendor:           ADSR
  version:          0.0.1
  name:             HTML entity decoder
  description:      Decode HTML entities in a JUCE String
  website:          http://www.adsrsounds.com
  license:          Boost 1.0

  dependencies:     juce_core

 END_JUCE_MODULE_DECLARATION

*******************************************************************************/

#pragma once
#define HTML_ENTITY_DECODER_H_INCLUDED

#include <juce_core/juce_core.h>
#include <map>

struct HTMLEntityDecoder
{
    static juce::String decode(const juce::String& input);

    static std::map<juce::String, unsigned int> entityMap;
};
