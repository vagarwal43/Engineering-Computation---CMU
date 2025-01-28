#include <iostream>
#include <cmath>
#include <limits>

// Function to interpolate
double interpolate(double x0, double y0, double x1, double y1, double x) {
	double y = y0 + ((y1-y0)/(x1-x0))*(x-x0);
	return y;
}

int main(void)
{
	// climb rate table
	double table[6][4]=
	{
		830.0,770.0,705.0,640.0,
		720.0,655.0,595.0,535.0,
		645.0,585.0,525.0,465.0,
		530.0,475.0,415.0,360.0,
		420.0,365.0,310.0,250.0,
		310.0,255.0,200.0,145.0
	};
	// Can be table[6][4] if it is easier.
	// double table[6][4]=
	// {
	// 	{830.0,770.0,705.0,640.0},
	// 	{720.0,655.0,595.0,535.0},
	// 	{645.0,585.0,525.0,465.0},
	// 	{530.0,475.0,415.0,360.0},
	// 	{420.0,365.0,310.0,250.0},
	// 	{310.0,255.0,200.0,145.0}
	// };

	const int num_alt = 6;										//number of altitudes
	const int num_temp = 4;
	double alt[num_alt] = {0,2000,4000,6000,8000,10000};		//altitudes array
	double temps[4] = {-20,0,20,40};							//temperature array
	double altitude, temperature;					//inputs
	bool c = true;									//counter variable

	//loop for input
	do{
		std::cout << "Enter Altitude and Temperature: ";
        std::cin >> altitude >> temperature;

		if (altitude < 0 || altitude > 10000 || temperature < -20 || temperature > 40){
			std::cout << "Altitude should be betweeb 0 and 10000ft and temperature should be between -20 and 40 Deg C";
			c = true;
		}
		else{
			c = false;
		}
	}while (c);

	double climb_rate = 0.0;	//climb_Rate to be found
	bool pre = false;			//counter variable if exact match is found

	//loop to see if the altitude and temp is already present
	for (int i = 0; i < 6; i++){
		if (alt[i] == altitude){
			for (int j = 0; j < 4; j++){
				if (temperature == temps[j]){
					climb_rate = table[i][j];	//climb rate taken
					pre = true;
				}
			}
		}
	}

	//if altitude doesn't match interpolation
	if(pre == false){

		int lower_alt_id = 0;									//lower altitutde index

		// finding the closest lower altitude
		while (lower_alt_id < num_alt - 1 && altitude > alt[lower_alt_id+1]){
			++lower_alt_id;		
		}
		int upper_alt_id = lower_alt_id +1;	//next upper altitude

		double lower_alt_rate = interpolate(temps[0], table[lower_alt_id][0], temps[3], table[lower_alt_id][3], temperature);	//interpolating to find the lower rate
		double upper_alt_rate = interpolate(temps[0], table[upper_alt_id][0], temps[3], table[upper_alt_id][3], temperature);	//interpolating to find the upper rate

		climb_rate = interpolate(alt[lower_alt_id],lower_alt_rate, alt[upper_alt_id],upper_alt_rate, altitude);	//interpolatin climb rate
	}

	std::cout << "Expected Climb Rate = " << climb_rate << "ft/min \n";

	return 0;
}
