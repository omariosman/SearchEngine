#include "Website.h"


Website::Website () {
	

}


string Website::get_url(){
	return url;
}


int Website::get_key(){
	return key;
}


int Website::get_impression(){
	return impression;
}

void Website::add_to_keywords(string word) {
	keywords.push_back(word);
}

bool Website::keyword_exists(const std::string &value, const std::vector<std::string> &keywords)
{
    return std::find(keywords.begin(), keywords.end(), value) != keywords.end();
}

void Website::set_url(string url_){
	url = url_;
}

void Website::set_key(int key_){
	key = key_;
}

void Website::set_impression(int impression_){
	impression =impression_;
}

void Website::set_keywords(vector<string> keywords_){
	keywords = keywords_;
}

void Website::printInfo() {
	cout << "url: " << url << endl;
	cout << "key: " << key << endl;
	cout << "impression: " << impression << endl;
	cout << "keywords: " << endl;
	for (int i = 1; i < keywords.size(); i++) {

		cout << keywords[i] << ",";
	}	
	cout << endl;
}

float Website::get_rank(){
	return rank;
}

void Website::set_rank(float rank_){
	rank = rank_;
}
