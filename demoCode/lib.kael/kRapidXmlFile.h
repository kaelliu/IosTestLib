//
//  kRapidXmlFile.h
//  xml parser wrapper class from rapidxml
//  Created by kael on 12/14/12.
//
//

#ifndef __kRapidXmlFile__
#define __kRapidXmlFile__
#include "rapidxml.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
using namespace std;
using namespace rapidxml;
template<class Ch=char>
class kRapidXmlFile
{
public:
    // load file into memory
    kRapidXmlFile(const char* filename)
    {
        // just read in
        basic_fstream<Ch> stream(filename,ios::in);
        if (!stream) {
            throw runtime_error(string("cann't open file")+filename);
        }
        // skip the write space
        stream.unsetf(ios::skipws);
        
        // get the file size
        stream.seekg(0,ios::end);
        size_t size = stream.tellg();
        stream.seekg(0);
        
        // load to data
        m_data.resize(size+1);
        stream.read(&m_data.front(),static_cast<streamsize>(size));
        m_data[size] = '\0';
    }
    
    kRapidXmlFile(std::basic_istream<Ch> & stream)
    {
        // skip the write space
        stream.unsetf(ios::skipws);
        m_data.assign(istreambuf_iterator<Ch>(stream), istreambuf_iterator<Ch>());
        if (stream.fail() || stream.bad())
            throw runtime_error("error reading stream");
        m_data.push_back(0);
    }
    
    Ch* data()
    {
        return  &m_data.front();
    }
    
    const Ch* data()const
    {
        return &m_data.front();
    }
    
    std::size_t size()const
    {
        return m_data.size();
    }
protected:
    std::vector<Ch> m_data;
};

// functions

// check the children count of node
template <class Ch>
inline std::size_t count_children(xml_node<Ch>* node)
{
    xml_node<Ch>* child = node->first_node();
    size_t count = 0;
    while (child) {
        ++count;
        child = child->next_sibling();
    }
    return count;
}

// check the attributes of node
template <class Ch>
inline std::size_t count_attributes(xml_node<Ch>* node)
{
    size_t count = 0;
    xml_attribute<Ch>* attr = node->first_attribute();
    while (attr) {
        ++count;
        attr = attr->next_attribute();
    }
    return count;
}

#endif /* defined(__kRapidXmlParser__) */
