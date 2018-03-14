#include <iostream>
#include <fstream>
#include <iomanip>

#include "McpeHandler.h"

int map(int argc, char** argv) {
	std::cout << "Map" << std::endl;

	if (argc<3)
	{
		std::cout << "Needs: database path" << std::endl;
		std::cout << "       output pnm file" << std::endl;		
		exit(1);
	}


	std::cout << "Database: " << argv[1] << std::endl;
	std::cout << "Output: " << argv[2] << std::endl;

	McpeHandler *h = new McpeHandler();
    
    h->loadLevelDB(argv[1]);
    h->findSizes();
    h->loadMap();

    h->savePNM(argv[2]);

    return 0;
}


int compact(int argc, char** argv) {
	std::cout << "Compact" << std::endl;

	if (argc<2)
	{
		std::cout << "Needs: database path" << std::endl;	
		exit(1);
	}


	std::cout << "Database: " << argv[1] << std::endl;

	McpeHandler *h = new McpeHandler();
    
    h->loadLevelDB(argv[1]);
    h->compact();
    
    return 0;
}


int sizes(int argc, char** argv) {
	std::cout << "Sizes" << std::endl;

	if (argc<2)
	{
		std::cout << "Needs: database path" << std::endl;
		exit(1);
	}


	std::cout << "Database: " << argv[1] << std::endl;

	McpeHandler *h = new McpeHandler();
    
    h->loadLevelDB(argv[1]);
    h->findSizes();

    return 0;
}

int erase(int argc, char** argv) {

	std::cout << "Erase" << std::endl;

	if (argc<6)
	{
		std::cout << "Needs: database path" << std::endl;
		std::cout << "       erase coordenates (x1 y1 x2 y2)" << std::endl;
		exit(1);
	}


	std::string dbname = argv[1];
    int x1 = atol(argv[2]);
    int y1 = atol(argv[3]);
    int x2 = atol(argv[4]);
    int y2 = atol(argv[5]);

	std::cout << "Database: " << dbname.c_str() << std::endl;
	std::cout << "Erase Area (" << x1 << ", " << y1 << ") to ("<< x2 << ", " << y2 << ")" << std::endl;

    McpeHandler d;
    
    d.loadLevelDB(dbname);
    d.erase(x1,y1,x2,y2);
   
   return 0;
}

int crop(int argc, char** argv) {

	std::cout << "Crop" << std::endl;

	if (argc<6)
	{
		std::cout << "Needs: database path" << std::endl;
		std::cout << "       crop coordenates (x1 y1 x2 y2)" << std::endl;
		exit(1);
	}


	std::string dbname = argv[1];
    int x1 = atol(argv[2]);
    int y1 = atol(argv[3]);
    int x2 = atol(argv[4]);
    int y2 = atol(argv[5]);

	std::cout << "Database: " << dbname.c_str() << std::endl;
	std::cout << "Crop Area (" << x1 << ", " << y1 << ") to ("<< x2 << ", " << y2 << ")" << std::endl;

    McpeHandler d;
    
    d.loadLevelDB(dbname);
    d.crop(x1,y1,x2,y2);
   
   return 0;
}

int merge (int argc, char** argv) {

	std::cout << "Merge" << std::endl;
	if (argc<6)
	{
		std::cout << "Needs: database source path" << std::endl;
		std::cout << "       database destination path" << std::endl;
		std::cout << "       destination coordenates (x y and z)" << std::endl;
		exit(1);
	}


	std::string source = argv[1];
	std::string dest = argv[2];
	int x = atol(argv[3]);
	int y = atol(argv[4]);
	int z = atol(argv[5]);

	std::cout << "Source Database: " << source.c_str() << std::endl;
 	std::cout << "Destination Database: " << dest.c_str() << std::endl;
	std::cout << "Merge into coordinates (" << x << ", " << y << ", " << z << ")" << std::endl;

	McpeHandler s;
    McpeHandler d;
    
    s.loadLevelDB(source);
	d.loadLevelDB(dest);
    
    d.addToMap(x,y,z,s);
    
    return 0;
}



int main(int argc, char** argv) {

	std::string command;
	if (argc>1) command = argv[1];
	

    if( command == "crop") {
        return crop(argc-1, argv+1);
    } else if( command == "erase") {
    	return erase(argc-1, argv+1);
    } else if( command == "merge") {
    	return merge(argc-1, argv+1);
    } else if( command == "map") {
        return map(argc-1, argv+1);
    } else if( command == "sizes") {
        return sizes(argc-1, argv+1);
    } else if( command == "compact") {
        return compact(argc-1, argv+1);
    } else {
        std::cout << argv[0] << " [command] [command options]" << std::endl;
        std::cout << " where command is one of: " << std::endl;
        std::cout << "     sizes       Finds map sizes " << std::endl;
        std::cout << "     crop        Crops map to specified coordenates " << std::endl;
        std::cout << "     erase       Erase specified coordenates from map" << std::endl;
        std::cout << "     merge       Merge source map into destination " << std::endl;
        std::cout << "     map         Creates an image map " << std::endl;
        std::cout << "     compact     Compacts map database " << std::endl;

        return 1;   	
    }

    return 0;
    
}
