import requests

url = "https://www.weatherunion.com/gw/weather/external/v0/get_locality_weather_data"

querystring = {"locality_id":"ZWL008599"}

headers = {"X-Zomato-Api-Key": "19d4219e1b6ad2c7b82708c802622a8e"}

response = requests.get(url, headers=headers, params=querystring)

#print(response.json())
data = response.json()

if data.get("status") == '200':
    # Extract the weather data
    weather_data = data.get("locality_weather_data", {})
    
    # Assign variables for each piece of data
    temperature = weather_data.get("temperature")
    humidity = weather_data.get("humidity")
    wind_speed = weather_data.get("wind_speed")
    wind_direction = weather_data.get("wind_direction")
    rain_intensity = weather_data.get("rain_intensity")
    rain_accumulation = weather_data.get("rain_accumulation")
    
    # Print the data in a nicely formatted way
    print("Weather Data for the Given Location: Miyapur")
    print(f"Temperature: {temperature} C")
    print(f"Humidity: {humidity}%")
    print(f"Wind Speed: {wind_speed} m/s")
    print(f"Wind Direction: {wind_direction}")
    print(f"Rain Intensity: {rain_intensity} mm/h")
    print(f"Rain Accumulation: {rain_accumulation} mm")
else:
    print("Failed to retrieve weather data.")
