#ifndef __NAMETEXTCONTROL_H__
#define __NAMETEXTCONTROL_H__

class AplhaNumCharIterator;

template<typename CharacterIteratorT = AplhaNumCharIterator>
class NameTextControl : public TextControl<StaticString<>, CharacterIteratorT> >
{

};

#endif /* __NAMETEXTCONTROL_H__ */