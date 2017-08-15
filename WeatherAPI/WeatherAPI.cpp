#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <cpprest/json.h>

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams

void weatherForecast();

int wmain() {
	weatherForecast();
	system("pause");
}

void weatherForecast() {
	utility::string_t url = L"http://api.openweathermap.org/data/2.5/weather?zip=";
	utility::string_t zip = L"";
	utility::string_t key = L",us&APPID=cdacce3f5637243105f60c9f48ab8b3a";

	std::wcout << "Please enter your zip code: ";
	std::wcin >> zip;

	url += zip + key;

	//Make a client
	http_client client1(url);

	//Convert response to json
	pplx::task<http_response> response = client1.request(methods::GET);
	http_response data = response.get();
	pplx::task<json::value> json = data.extract_json();
	json::value& weatherData = json.get();

	//Print JSON object
	std::wcout << "Weather data for " << zip << " is: " << weatherData << std::endl;

	//Parse JSON
	double temp = weatherData.at(U("main")).at(U("temp")).as_double();

	std::wcout << "\nTemperature in Kelvin: " << temp << std::endl;

	//Convert Kelvin to Fahrenheit
	double fahrenheit = ((9.00 / 5.00) * (temp - 273.00)) + 32.00;
	std::wcout << "\nTemperature in Fahrenheit: " << fahrenheit << std::endl;
}