//          Copyright Rich Elmes 2019
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifdef HTML_ENTITY_DECODER_H_INCLUDED
/* When you add this cpp file to your project, you mustn't include it in a file where you've
 already included any other headers - just put it inside a file on its own, possibly with your config
 flags preceding it, but don't include anything else. That also includes avoiding any automatic prefix
 header files that the compiler may be using.
 */
#error "Incorrect use of HTML Entity Decoder cpp file"
#endif

#include "html_entity_decoder.h"

juce::String HTMLEntityDecoder::decode(const juce::String& input)
{
    auto charPointer = input.getCharPointer();
    const auto endOfString = charPointer.findTerminatingNull();

    juce::String decodedString;
    juce::String currentEntity;
    bool searchingForEntity = false;

    while(charPointer != endOfString)
    {
        const auto currentChar = charPointer.getAndAdvance();
        if(currentChar != '&' && !searchingForEntity)
        {
            decodedString += currentChar;
        }
        else
        {
            if(currentChar == ';')
            {
                auto entity = entityMap.find(currentEntity);
                if(entity != entityMap.end())
                {
                    decodedString += juce::juce_wchar(entity->second);
                }
                else
                {
                    if(currentEntity.startsWith("#"))
                    {
                        // numbered entity
                        decodedString += juce::juce_wchar(currentEntity.substring(1).getIntValue());
                    }
                    else
                    {
                        // couldn't find entity, just write back what we found
                        decodedString += "&" + currentEntity + ";";
                    }
                }
                currentEntity.clear();
                searchingForEntity = false;
            }
            else
            {
                if(currentChar != '&')
                {
                    currentEntity += currentChar;
                }
                searchingForEntity = true;
            }
        }
    }

    // in case we got to the end whilst trying to find an entity, append it
    if(currentEntity.isNotEmpty())
    {
        decodedString += "&" + currentEntity;
    }

    return decodedString;
}

std::map<juce::String, unsigned int> HTMLEntityDecoder::entityMap = {
    { "amp", 38 },
    { "lt", 60 },
    { "gt", 62 }
};
