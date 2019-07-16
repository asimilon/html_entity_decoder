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
    { "gt", 62 },
    { "nbsp", 160 },
    { "iexcl", 161 },
    { "cent", 162 },
    { "pound", 163 },
    { "curren", 164 },
    { "yen", 165 },
    { "copy", 169 },
    { "laquo", 171 },
    { "reg", 174 },
    { "deg", 176 },
    { "raquo", 187 },
    { "iquest", 191 },
    { "Agrave", 192 },
    { "Aacute", 193 },
    { "Acirc", 194 },
    { "Atilde", 195 },
    { "Auml", 196 },
    { "Aring", 197 },
    { "AElig", 198 },
    { "Ccedil", 199 },
    { "Egrave", 200 },
    { "Eacute", 201 },
    { "Ecirc", 202 },
    { "Euml", 203 },
    { "Igrave", 204 },
    { "Iacute", 205 },
    { "Icirc", 206 },
    { "Iuml", 207 },
    { "ETH", 208 },
    { "Ntilde", 209 },
    { "Ograve", 210 },
    { "Oacute", 211 },
    { "Ocirc", 212 },
    { "Otilde", 213 },
    { "Ouml", 214 },
    { "times", 215 },
    { "Oslash", 216 },
    { "Ugrave", 217 },
    { "Uacute", 218 },
    { "Ucirc", 219 },
    { "Uuml", 220 },
    { "Yacute", 221 },
    { "THORN", 222 },
    { "szlig", 223 },
    { "agrave", 224 },
    { "aacute", 225 },
    { "acirc", 226 },
    { "atilde", 227 },
    { "auml", 228 },
    { "aring", 229 },
    { "aelig", 230 },
    { "ccedil", 231 },
    { "egrave", 232 },
    { "eacute", 233 },
    { "ecirc", 234 },
    { "euml", 235 },
    { "igrave", 236 },
    { "iacute", 237 },
    { "icirc", 238 },
    { "iuml", 239 },
    { "eth", 240 },
    { "ntilde", 241 },
    { "ograve", 242 },
    { "oacute", 243 },
    { "ocirc", 244 },
    { "otilde", 245 },
    { "ouml", 246 },
    { "divide", 247 },
    { "oslash", 248 },
    { "ugrave", 249 },
    { "uacute", 250 },
    { "ucirc", 251 },
    { "uuml", 252 },
    { "yacute", 253 },
    { "thorn", 254 },
    { "yuml", 255 },
    { "lsquo", 8216 },
    { "rsquo", 8217 },
    { "ldquo", 8220 },
    { "rdquo", 8221 },
    { "euro", 8364 },
    { "trade", 8482 }
};
