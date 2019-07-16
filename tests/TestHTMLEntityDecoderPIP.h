/*******************************************************************************
 The block below describes the properties of this PIP. A PIP is a short snippet
 of code that can be read by the Projucer and used to generate a JUCE project.

 BEGIN_JUCE_PIP_METADATA

  name:             TestHTMLEntityDecoder

  dependencies:     juce_core, juce_data_structures, juce_events
  exporters:        xcode_mac

  moduleFlags:      JUCE_STRICT_REFCOUNTEDPOINTER=1

  type:             Console

 END_JUCE_PIP_METADATA

*******************************************************************************/

#pragma once


//==============================================================================

void outputError(const String& testName, const String& expected, const String& result)
{
    std::cout << testName << " test failed!" << std::endl;
    std::cout << "Expected : " << expected << std::endl;
    std::cout << "Result   : " << result << std::endl;
}

#define TEST(NAME, INPUT, EXPECTED) {\
String inString = INPUT; \
String expectedString = EXPECTED; \
auto decodedString = HTMLEntityDecoder::decode(inString); \
if(decodedString != expectedString) { \
outputError(NAME, expectedString, decodedString); \
return 1;\
} }

int main (int argc, char* argv[])
{
    TEST("&amp;", "Something &amp; another thing!", "Something & another thing!");
    TEST("&lt;", "69 &lt; 666 is true.", "69 < 666 is true.");
    TEST("&gt;", "123 &gt; 999 is false;", "123 > 999 is false;");
    TEST("No entity", "There is no HTML entity here!", "There is no HTML entity here!");
    TEST("Not an entity", "Test that &nonsense; is not a supported entity!", "Test that &nonsense; is not a supported entity!")
    TEST("Entity doesn't end", "War & Peace is a novel!", "War & Peace is a novel!");
    TEST("Multiple entities", "We can use &lt;html&gt; entities!", "We can use <html> entities!");
    TEST("Numbered entities", "&#65;&#66;&#67;", "ABC");
    TEST("Zero length entity", "Zero length entity like &; will be ignored.", "Zero length entity like &; will be ignored.");

    // test all entities in the map
    for(auto& entity : HTMLEntityDecoder::entityMap)
    {
        String input = entity.first;
        auto expected = String::charToString(juce_wchar(entity.second));
        auto decoded = HTMLEntityDecoder::decode("&" + input + ";");
        if(decoded != expected)
        {
            outputError(entity.first, expected, decoded);
            return 1;
        }
    }

    std::cout << "All tests passed!" << std::endl;

    return 0;
}
