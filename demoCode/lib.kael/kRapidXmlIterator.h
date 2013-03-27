//
//  kRapidXmlIterator.h
//
//  Created by kael on 12/17/12.
//
//

#ifndef _kRapidXmlIterator_h
#define _kRapidXmlIterator_h

#include "rapidxml.hpp"

//! Iterator of child nodes of xml_node
template<class Ch>
class kNodeIterator
{
public:
    typedef typename xml_node<Ch> value_type;
    typedef typename xml_node<Ch> &reference;
    typedef typename xml_node<Ch> *pointer;
    typedef std::ptrdiff_t difference_type;
    typedef std::bidirectional_iterator_tag iterator_category;
    kNodeIterator()
    : m_node(0)
    {
        
    }
    
    kNodeIterator(xml_node<Ch> *node)
    : m_node(node->first_node())
    {
        
    }
    
    reference operator *() const
    {
        assert(m_node);
        return *m_node;
    }
    
    pointer operator->() const
    {
        assert(m_node);
        return m_node;
    }
    
    node_iterator& operator++()
    {
        assert(m_node);
        m_node = m_node->next_sibling();
        return *this;
    }
    
    node_iterator operator++(int)
    {
        node_iterator tmp = *this;
        ++this;
        return tmp;
    }
    
    node_iterator& operator--()
    {
        assert(m_node && m_node->previous_sibling());
        m_node = m_node->previous_sibling();
        return *this;
    }
    
    node_iterator operator--(int)
    {
        node_iterator tmp = *this;
        ++this;
        return tmp;
    }
    
    bool operator ==(const node_iterator<Ch> &rhs)
    {
        return m_node == rhs.m_node;
    }
    
    bool operator !=(const node_iterator<Ch> &rhs)
    {
        return m_node != rhs.m_node;
    }
protected:
    xml_node<Ch>* m_node;
};

template<class Ch>
class kAttributeIterator
{
public:
    typedef typename xml_attribute<Ch> value_type;
    typedef typename xml_attribute<Ch>& reference;
    typedef typename xml_attribute<Ch>* pointer;
    typedef typename std::ptrdiff_t difference_type;
    typedef typename std::bidirectional_iterator_tag iterator_category;
    
    kAttributeIterator()
    : m_attribute(0)
    {
    }
    
    kAttributeIterator(xml_node<Ch> *node)
    : m_attribute(node->first_attribute())
    {
    }
    
    reference operator *() const
    {
        assert(m_attribute);
        return *m_attribute;
    }
    
    pointer operator->() const
    {
        assert(m_attribute);
        return m_attribute;
    }
    
    attribute_iterator& operator++()
    {
        assert(m_attribute);
        m_attribute = m_attribute->next_attribute();
        return *this;
    }
    
    attribute_iterator operator++(int)
    {
        attribute_iterator tmp = *this;
        ++this;
        return tmp;
    }
    
    attribute_iterator& operator--()
    {
        assert(m_attribute && m_attribute->previous_attribute());
        m_attribute = m_attribute->previous_attribute();
        return *this;
    }
    
    attribute_iterator operator--(int)
    {
        attribute_iterator tmp = *this;
        ++this;
        return tmp;
    }
    
    bool operator ==(const attribute_iterator<Ch> &rhs)
    {
        return m_attribute == rhs.m_attribute;
    }
    
    bool operator !=(const attribute_iterator<Ch> &rhs)
    {
        return m_attribute != rhs.m_attribute;
    }
protected:
    xml_attribute<Ch>* m_attribute;
};

#endif
