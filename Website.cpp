#include "Website.h"


Website::Website () {
	click = 0.0;

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

float Website::get_normalized_rank(){
	return normalized_rank;
}

void Website::set_normalized_rank(float normalized_rank_){
	normalized_rank = normalized_rank_;
}

void Website::set_CTR(float CTR_){
	CTR = CTR_;
}

void Website::set_click(float click_){
	click = click_;
}

float Website::get_CTR(){
	return CTR;
}
float Website::get_click(){
	return click;
}

void Website::calculate_CTR(){
	float numerator = click;
	int deno = impression;
	CTR = (numerator / deno) * 100.0;
	cout << "CTR: " << CTR << endl;
}

void Website::increment_click(){
	click++;
}

void Website::calculate_score(){
	calculate_CTR();
	float _1st_comp = 0.4 * normalized_rank;
	cout << "1st: " << _1st_comp << endl;
	float _2nd_comp_nume = 0.1 * impression;
	float _2nd_comp_deno = 1 + (0.1 * impression);
	float _2nd_comp = _2nd_comp_nume / _2nd_comp_deno;
	float _3rd_comp = 1 - _2nd_comp;
	float _4th_comp = _3rd_comp * normalized_rank;
	float _5th_comp = _2nd_comp * CTR;
	float _6th_comp = _5th_comp + _4th_comp;
	float _7th_comp = _6th_comp * 0.6;
	float final_comp = _1st_comp + _7th_comp;
	score = final_comp; 
}

float Website::get_score(){
	return score;
}











