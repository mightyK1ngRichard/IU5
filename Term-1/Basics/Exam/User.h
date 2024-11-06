#pragma once
#include "Header.h"

class User {
public:
	User();
	~User();

	void SendUserName(const std::string&);
	void SendUserLanguages(const std::vector<std::string>&);
	std::string GetUserName() const;
	std::vector<std::string> GetUserLanguages() const;
	size_t GetUserID() const;
	void AddNewLanguage(const std::string&);

private:
	static size_t _count_users;
	const size_t _user_ID;
	std::string _user_name;
	size_t _user_age;
	std::vector<std::string> _user_languages;
};
size_t User::_count_users = 0;
User::User() : _user_age(0), _user_ID(_count_users + 1) {
	++_count_users;
}
User::~User() = default;
inline void User::SendUserLanguages(const std::vector<std::string>& vec) {
	_user_languages = vec;
}
inline void User::SendUserName(const std::string& name) {
	_user_name = name;
}
inline std::vector<std::string> User::GetUserLanguages() const {
	return _user_languages;
}
inline std::string User::GetUserName() const {
	return _user_name;
}
inline size_t User::GetUserID() const {
	return _user_ID;
}
inline void User::AddNewLanguage(const std::string& language) {
	_user_languages.push_back(language);
}

