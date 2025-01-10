import requests

# OpenWeatherMap
API_URL = "http://api.openweathermap.org/data/2.5/weather"
API_KEY = "29526be92f5dbb2ce80c0af2de7ba65e"  

def get_weather(city):

    params = {
        "q": city,
        "appid": API_KEY,
        "units": "metric"  }
    response = requests.get(API_URL, params=params)
    if response.status_code == 200:
        data = response.json()  

        city_name = data["name"]
        country = data["sys"]["country"]
        temp = data["main"]["temp"]
        weather = data["weather"][0]["description"]
        humidity = data["main"]["humidity"]
        wind_speed = data["wind"]["speed"]
        print(f"Weather in {city_name}, {country}:")
        print(f"Temperature: {temp}°C")
        print(f"Condition: {weather}")
        print(f"Humidity: {humidity}%")
        print(f"Wind Speed: {wind_speed} m/s")
    else:
        print("City not found or API limit exceeded. Please try again.")
print("Welcome to SkySync")        
city = input("Enter the city name: ")
get_weather(city) 
