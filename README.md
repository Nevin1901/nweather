# nweather

A simple command line tool which allows you to get the weather from any country, and more

![1](images/1.png)

## Info
nweather is primarily a command line program made for getting the weather and other information about it. It is mainly meant for unix, but it should compile on windows just fine.
I mainly created this as a way for me to learn more about c++, and I plan to add more features

## Usage
```
-i (imperial) -k (kelvin) | Both of these are optional. Defaults to metric
nweather Country 'Country Name'
nweather -h Country 'County Name'
nweather -c lat long
nweather -r lat long count
```

## Building
`make`
Then move to /bin/

## Todo
* Add a flag which will output an emoji based on description
* Add a flag which will show stats about the weather in one line, which could be used in your statusbar
