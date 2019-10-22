using namespace std;
#include <fstream>
#include <iostream>
#include <string>

class Instruments :
	public Airplane
{
protected:
	double c_travelleddistance, c_fuelconsumed, c_altitude, c_verticalspeed, c_remainingdistance, c_remainingfuel; //The output parameters

public:
	Instruments();
	
	//Running calculator for Altitude, Remaining distance, remaining fuel
	//Climbing speed is 40 feets per nautical mile (1.852 km) travelled by airplane
	void runningcalcs(double totaldistance, double Hspeed, double fuelamount, double frameupdate);

	//Printing out updated instruments reading
	void print();

	//Crash function if instruments fail
	void crash(); //Concerete function

	//Setters for Instruments class variables
	inline void setFuelConsumed(double fuel) { c_fuelconsumed = fuel; }
	inline void setAltitude(double altitude) { c_altitude = altitude; }
	inline void setTravelleddistance(double distance) { c_travelleddistance = distance; }

	//Getters for Instrument class variables
	inline double getFuelConsumed() { return c_fuelconsumed; }
	inline double getTravelleddistance() { return c_travelleddistance; }
	inline double getAltitude() { return c_altitude; }
	
	//Destructor for instrument class
	~Instruments();
};

class Airplane
{
protected:
	//Inputs required before airplane takes off

	double c_totaldistance, c_highesspeed, c_amountoffuel, c_frameupdatetime; 

	//Inputs for control of airplane as and when required
	//All inputs should be in degrees

	double c_flaw, c_pitch, c_roll;

public:
	//Constructor for basic inputs before the flight takes off
	Airplane(); 

	//Pre flight data intakes
	void preflightdata();

	//Pilot control function
	void pilotcontrols(); 

	//Crash function called if any of the condition is satisfied in pilotcontrols()
	void crash();

	//Default destructor
	~Airplane();

	// Just in case if required, Getters and Setters 

	inline void setTotalDistance(double distance) { c_totaldistance = distance; }
	inline void setTotalFuelAmount(double fuel) { c_amountoffuel = fuel; }
	inline void setTimeframe(double timeframe) { c_frameupdatetime = timeframe; }
	inline void setSpeed(double speed) { c_highesspeed = speed; }

	inline double getTotalDistance() { return c_totaldistance; }
	inline double getTotalFuel() { return c_amountoffuel; }
	inline double getTimeFrame() { return c_frameupdatetime; }
	inline double getSpeed() { return c_highesspeed; }
};

Instruments::Instruments() //Assiging all the output parameters initially to zeroes
{
	c_altitude = 0; //Stores running alitude, Altitudometer
	c_fuelconsumed = 0; //Fuel Guage readings
	c_travelleddistance = 0; 
	//Variometer, cannot be measured by ground speed or actual speed. Measured by air pressure outside
	c_remainingfuel = 0;
	c_remainingdistance = 0;
}

void Instruments:: runningcalcs(double totaldistance, double Hspeed, double fuelamount, double frameupdate)
{
	//Calculates the remaining distance based on speed input and time updates as requested by pilot
	c_travelleddistance += ((Hspeed*frameupdate) / 60); 
	//c_remainingdistance = totaldistance - c_travelleddistance;

	//Calculates the fuel consumption based on distance travelled from above eqaution
	c_fuelconsumed += ((Hspeed*frameupdate / 60) * 12);
	//c_remainingfuel = fuelamount - c_fuelconsumed;

	//Calculates the altitude based on time of flight, i.e. 1 nautical mile = 40 feets climb
	
	if (c_altitude <= 5000)
	{
		//According to Boeing, the maximum height airplane travels is 45000 fts, keeping it low
		c_altitude += (Hspeed * (frameupdate / 60) * (12.192/1.852)); //40 fts = 12.192 meters, 1 nautical mile = 1.852 km
	}
	else
	{
		//Does nothing since maximum altitude has reached 
	}

	setFuelConsumed(c_fuelconsumed);
	setTravelleddistance(c_travelleddistance);
	setAltitude(c_altitude);
}

void Instruments::print()
{
	cout << endl << endl << "Altitude (m)\tFuel Consumed (L)\tDistance Travelled (km)" << endl;
	cout << getAltitude() << "\t\t\t" << getFuelConsumed() << "\t\t\t" << getTravelleddistance() << endl;
}

void Instruments::crash() //Concerete function Crash()
{
	cout << endl << "The plane has crashed due to insufficient fuel or low altitude" << endl;
}

Instruments::~Instruments()
{

}

Airplane::Airplane()
{	
	c_amountoffuel = c_frameupdatetime = c_highesspeed = c_highesspeed = c_flaw = c_pitch = c_roll = 0; 
	//Initially all zeroes
}

void Airplane::preflightdata()
{
	while (true) //Minimum distance required is 5000
	{
		cout << endl << "Enter the total flight distance (km) : ";
		cin >> c_totaldistance;

		if (c_totaldistance > 1000)
		{
			break;
		}
	}

	while (c_highesspeed < 600) //Minimum speed required 600 km/h
	{
		cout << endl << "Enter the speed (km/h) : ";
		cin >> c_highesspeed;
	}

	while (c_amountoffuel < 100000) //Minimum fuel amount required 125k liters
	{
		cout << endl << "Enter total fuel (liters) : ";
		cin >> c_amountoffuel;
	}

	while (c_frameupdatetime <= 5 || c_frameupdatetime >= 25)
		//Minimum timeframe is 5 seconds (aka 5 minutes for program sake) max 25 seconds
	{
		cout << endl << "Enter instrument update frametime (minutes) : ";
		cin >> c_frameupdatetime;
	}
}

Airplane::~Airplane() {}

void Airplane::crash() //Crash function incase if airplane falls 
{
	cout << endl << "The simulation has ended. The airplane crashed :( RIP!!!!";
	exit(0);
}

void Airplane::pilotcontrols()
{
	int choice = 0;
	double temp_pitch = 0, temp_flaw = 0, temp_roll = 0;

	while(true)
	{ 
		cout <<endl << "Select one of the controls\n0. Do Nothing\n1. Pitch\n2. Flaw\n3. Roll\n\nEnter your choice : ";
		cin >> choice;

		if (choice == 1 || choice == 2 || choice == 3 || choice == 0)
		{
			break;
		}
		else
		{
			true;
		}
	}
	
	cout << endl << "Ensure that all measurements are in degrees";
	
	if (choice == 0)
	{
		//Does nothing. The pilot wants the airplane to fly in same conditions as before
	}

	else if (choice == 1) //Runs this condition if pilot selects 1
	{
		cout << endl << "Enter angle of pitch of airplane : "; //Input for pitch angle
		cin >> temp_pitch;

		c_pitch += temp_pitch; //Adding total pitch angle

		if (c_pitch >= 17) //If the total pitch angle reaches 17, the airplane crashes
		{
			crash(); //Calling the crash function
		}
	}

	else if (choice == 2) //Runs this condition if pilot selects 2
	{
		cout << endl << "Enter angle of flaw of airplane : "; //Input for flaw angle
		cin >> temp_flaw;
		c_flaw += temp_flaw; //Adding total flaw angle

		if (c_flaw >= 10) //If the total roll angle reaches 10, the airplane crashes
		{
			crash(); //Calling the crash function
		}
	}

	else if (choice == 3) //Runs this condition if pilot selects 3
	{
		cout << endl << "Enter angle of roll of airplane : "; //Input for roll angle
		cin >> temp_roll;

		c_roll += temp_roll; //Running sum of roll angle

		if (c_roll >= 45) //If the total roll angle reaches 45, the airplane crashes
		{
			crash(); //Calling the crash function
		}
	}
}

int main()
{
	cout << "This is an simulation assuming that airplane has taken off from the runway. ";
	cout << endl << "There are multiple inputs required before program executes." << endl;
	cout << "This program would display every result in seconds but the instruments are calibrated for time in take in minutes" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "Minimum distance : 5000 km\nMinimum Speed : 600 km/h\nMinimum Fuel requirement : 100,000 liters\nTimeFrame for Output : 5 seconds to 25 seconds\nFlight uses 12 L per km\nMaximum Altitude = 5000 m +/- 300 m\n-------------------------------------------------------------------------" << endl;

	//Output file only, doesn't override past informations, adds new one.
	ofstream datafile;
	datafile.open("Instrumentslogs.txt", ios::out | ios::app); 

	Airplane airplane; //Creating instance of Airplane class for prior takeoff data input
	Instruments instruments; //Creating an instance of Instrument class for constructor initialization

	airplane.preflightdata(); //Function that runs only once to take pre-flight departure data
	
	//Firstly, writing headings to the file
	datafile << "Altitude\tRem. fuel\tRemaining distance" << endl;

	int n = 0; //Variable that would keep a count for asking pilot if they want to change airplane's config.

	while (airplane.getTotalFuel() > instruments.getFuelConsumed() && airplane.getTotalDistance() > instruments.getTravelleddistance())
	{ 
		if (airplane.getTotalFuel() > 0) //Condition check if fuel is available to fly
		{
			if (n % 5 == 0) //Runs the below function when condition becomes true
			{
				airplane.pilotcontrols(); //Once every 5 times
			}

			//Instrument function call
			instruments.runningcalcs(airplane.getTotalDistance(), airplane.getSpeed(), airplane.getTotalFuel(), airplane.getTimeFrame());

			instruments.print(); //Print function from derived class which purely prints the instrumemt readings

			//Writing the data to the file to keep the track records of all instruments, i.e. altitude measuring, Fuel Gauge and Distance remaining
			datafile << instruments.getAltitude() << "\t\t" << instruments.getFuelConsumed() << "\t\t" << instruments.getTravelleddistance() << endl;

			//AirplaneStatus = true; //Ensuring and assigning the airplanestatus variable true value so that loop keeps running
		}
		else
		{
			airplane.crash();
			//AirplaneStatus = false;
		}
		Sleep(airplane.getTimeFrame() * 1000); 
		//Timed out syntax, The program goes to sleep for user defined seconds and generates the output once back on.

		n++; //Increment 'n' by 1
	}

	datafile.close(); //Closing the Instrument log file
}