#include "isstring.h"
#include "util.h"

const string ISString::nullStdString;

/** Constructs an ISString with str data. */
ISString::ISString(const char *str): data(0) {
	if (str && str[0] != '\0') {
		data = new SharedData(string(str));
	}
}

/** Constructs an ISString with str data. */
ISString::ISString(const string &str): data(0){
	if (str.length() != 0) data = new SharedData(str);
}

/** Copy constructor */
ISString::ISString(const ISString &str): data(str.data) {
	if (data != 0) {
		++data->refCounter;
		return;
	}
}

/** Destructor */
ISString::~ISString() {
	if (data) {
		data->decreaseRefCount();
	}
}

/** Assignment operator */
ISString & ISString::operator=(const ISString &o) {
	if (data != 0) data->decreaseRefCount();
	data = o.data;
	if (data != 0) data->increaseRefCount();
	return *this;
}

/** Returns copy of string data. */
string ISString::getStdString()const{
	if (data == 0) return string();
	return data->str;
}

/** Returns a reference to string data.
  * This reference will be valid until all references to the underlying string are destroyed. */
const string &ISString::getRef()const {
	if (data == 0) return nullStdString;
	return data->str;
}

/** Returns the number of characters in the string */
size_t ISString::length() const {
	if (data == 0) return 0;
	return data->str.length();
}

/** Returns true if string is empty, false otherwise. */
bool ISString::empty() const {
	if (data == 0) return true;
	return data->str.empty();
}

/** Equality operator */
bool ISString::operator==(const ISString &o) const {
	if (this->data == 0) {
		if (o.data == 0) return true;
		return false;
	}
	if (o.data == 0) return false;
	return o.data->str == data->str;
}

/** Unequality operator */
bool ISString::operator!=(const ISString &o) const {
	if (this->data == 0) {
		if (o.data == 0) return false;
		return true;
	}
	if (o.data == 0) return true;
	return o.data->str != data->str;
}

/** Addition operator */
ISString ISString::operator+(const ISString &o) const {
	if (o.data == 0) {
		return *this;
	}
	if (data == 0) {
		return o;
	}
	ISString s(data->str+o.data->str);
	s.data->noNeedForEncoding = o.data->noNeedForEncoding && this->data->noNeedForEncoding;
	return s;
}

/** Addition operator */
ISString ISString::operator+(const string &o) const{
	if (data == 0) {
		return o;
	}

	return ISString(data->str+o);
}

/** Converts the string to a int. Will return 0 if conversion fails.*/
int32_t ISString::toInt() const {
	if (data == 0) return 0;
	try {
		return (boost::lexical_cast<int32_t>(data->str));
	}
	catch (boost::bad_lexical_cast &) {
		return 0;
	}
}

/** Converts the string to a float. Will return 0 if conversion fails.*/
float ISString::toFloat() const {
	if (data == 0) return 0.0f;
	try {
		return (boost::lexical_cast<float>(data->str));
	}
	catch (boost::bad_lexical_cast &) {
		return 0.0f;
	}
}

/** Converts the string to a byte. Will return 0 if conversion fails.*/
uint8_t ISString::toByte() const {
	if (data == 0) return 0;
	try {
		return (boost::lexical_cast<uint8_t>(data->str));
	}
	catch (boost::bad_lexical_cast &) {
		return 0;
	}
}

/** Converts the string to a short. Will return 0 if conversion fails.*/
uint16_t ISString::toShort()const{
	if (data == 0) return 0;
	try {
		return (boost::lexical_cast<uint16_t>(data->str));
	}
	catch (boost::bad_lexical_cast &) {
		return 0;
	}
}

/** std::string and ISString addition operator */
ISString operator +(const string &a,const ISString&b) {
	if (b.data == 0) return a;
	return a+b.data->str;
}

/** Returns a reference to the UTF-8 encoded string data.
  * This reference will be valid until all references to the underlying string are destroyed. */
const string &ISString::getUtf8Encoded() const {
	if (this->data == 0) return nullStdString;
	if (this->data->noNeedForEncoding) {return this->data->str;}
	if (this->data->utfStr == 0) {
		this->data->utfStr = new string;
		this->data->utfStr->assign(CP1252toUtf8(this->data->str));
	}
	return *this->data->utfStr;
}

/** Returns true if the left operand is considered greater than the right operand, otherwise returns false. */
bool ISString::operator >(const ISString &o) const {
	if (this->data == 0) {
		return false;
	}
	if (o.data == 0) {
		return true;
	}
	if (this->data->str.compare(o.data->str) > 0) {
		return true;
	}
	return false;
}

/** Returns true if the left operand is considered smaller than the right operand, otherwise returns false. */
bool ISString::operator <(const ISString &o) const {
	if (o.data == 0) {
		return false;
	}
	if (this->data == 0) {
		return true;
	}
	if (this->data->str.compare(o.data->str) < 0) {
		return true;
	}
	return false;
}

/** Returns true if the left operand is considered smaller than or equal to the right operand, otherwise returns false. */
bool ISString::operator >=(const ISString &o) const {
	if (o.data == 0) {
		return true;
	}
	if (this->data == 0) {
		return false;
	}
	if (this->data->str.compare(o.data->str) >= 0) {
		return true;
	}
	return false;
}

/** Returns true if the left operand is considered smaller than or equal to the right operand, otherwise returns false. */
bool ISString::operator <=(const ISString &o) const {
	if (this->data == 0) {
		return true;
	}
	if (o.data == 0) {
		return false;
	}
	if (this->data->str.compare(o.data->str) <= 0) {
		return true;
	}
	return false;
}

/** Get a pointer to ALLEGRO_PATH from the string inside */
ALLEGRO_PATH* ISString::getPath() const {
	if (data == 0) return al_create_path(NULL);
	return al_create_path(data->str.c_str());
}

/** Disables or enables string utf-8 encoding in getUtf8Encoded. By default encoding is enabled.*/
void ISString::requireEncoding(bool t) {
	if (this->data) this->data->noNeedForEncoding = !t;
}

bool ISString::isEncodingRequired() const {
	if (this->data && !this->data->noNeedForEncoding) return true;
	return false;
}
