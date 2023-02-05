#pragma once

enum class BoxType //box types to use when creating objects
{
	Red,
	Yellow,
	Green,
	Blue,
	White       //unused
};

enum class Score //score settings
{
	Fail = -50,
	None = 0,
	White = 10,
	Green = 25,
	Yellow = 50,
	Blue = 75,
	Red = 100
};

enum class SpeedType //difficulty
{
	Easy = 50,
	Normal = 300,
	Hard = 500,
	Extreme = 750,
	Impossible = 1000
};

enum class Option //menu, pause options
{
	None = -1,
	Quit,
	Start,
	Resume,
	Settings		//unused
};