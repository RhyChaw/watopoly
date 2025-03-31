#ifndef POSITIONARRAY_H
#define POSITIONARRAY_H
#include <iostream>
#include <vector>
#include <string>
#include <map>

const std::vector<std::vector<std::string>> OWNABLE = {
    {"AL", "Arts1", "40", "50", "2", "10", "30", "90", "160", "250"},
    {"ML", "Arts1", "60", "50", "4", "20", "60", "180", "320", "450"},
    {"ECH", "Arts2", "100", "50", "6", "30", "90", "270", "400", "550"},
    {"PAS", "Arts2", "100", "50", "6", "30", "90", "270", "400", "550"},
    {"HH", "Arts2", "120", "50", "8", "40", "100", "300", "450", "600"},
    {"RCH", "Eng", "140", "100", "10", "50", "150", "450", "625", "750"},
    {"DWE", "Eng", "140", "100", "10", "50", "150", "450", "625", "750"},
    {"CPH", "Eng", "160", "100", "12", "60", "180", "500", "700", "900"},
    {"LHI", "Health", "180", "100", "14", "70", "200", "550", "750", "950"},
    {"BMH", "Health", "180", "100", "14", "70", "200", "550", "750", "950"},
    {"OPT", "Health", "200", "100", "16", "80", "220", "600", "800", "1000"},
    {"EV1", "Env", "220", "150", "18", "90", "250", "700", "875", "1050"},
    {"EV2", "Env", "220", "150", "18", "90", "250", "700", "875", "1050"},
    {"EV3", "Env", "240", "150", "20", "100", "300", "750", "925", "1100"},
    {"PHYS", "Sci1", "260", "150", "22", "110", "330", "800", "975", "1150"},
    {"B1", "Sci1", "260", "150", "22", "110", "330", "800", "975", "1150"},
    {"B2", "Sci1", "280", "150", "24", "120", "360", "850", "1025", "1200"},
    {"EIT", "Sci2", "300", "200", "26", "130", "390", "900", "1100", "1275"},
    {"ESC", "Sci2", "300", "200", "26", "130", "390", "900", "1100", "1275"},
    {"C2", "Sci2", "320", "200", "28", "150", "450", "1000", "1200", "1400"},
    {"MC", "Math", "350", "200", "35", "175", "500", "1100", "1300", "1500"},
    {"DC", "Math", "400", "200", "50", "200", "600", "1400", "1700", "2000"},
    {"PAC", "Gym", "150", "0", "0", "0", "0", "0", "0", "0"},
    {"CIF", "Gym", "150", "0", "0", "0", "0", "0", "0", "0"},
    
    {"MKV", "Residence", "200"},
    {"UWP", "Residence", "200"},
    {"V1", "Residence", "200"},
    {"REV", "Residence", "200"},

    {"OSAP", "0", "0", "0", "0", "0", "0", "0", "0", "0"},
    {"SLC", "0", "0", "0", "0", "0", "0", "0", "0", "0"},
    {"NeedlesHall", "0", "0", "0", "0", "0", "0", "0", "0", "0"},
    {"TimsLine", "0", "0", "0", "0", "0", "0", "0", "0", "0"},
    {"GooseNesting", "0", "0", "0", "0", "0", "0", "0", "0", "0"},
    {"NeedlesHall", "0", "0", "0", "0", "0", "0", "0", "0", "0"},
    {"TimsLine", "GO TO TIMS"},
    {"NeedlesHall", "0", "0", "0", "0", "0", "0", "0", "0", "0"},
    {"CoopFee", "COOP FEE"}
};

const std::vector<std::string> BOARD = 
{
    "COLLECT OSAP", "AL", "SLC", "ML", "TUITION", "MKV", "ECH", "NEEDLES HALL", "PAS", "HH", 
    "DC Tims Line", "RCH", "PAC", "DWE", "CPH", "UWP", "LHI", "SLC", "BMH", "OPT",
    "Goose Nesting", "EV1", "NEEDLES HALL", "EV2", "EV3", "V1", "PHYS", "B1", "CIF", "B2",
    "GO TO TIMS", "EIT", "ESC", "SLC", "C2", "REV", "NEEDLES HALL", "MC", "COOP FEE", "DC",
};

const std::map<std::string, int> IMPR = {
    {"AL", 0}, {"ML", 0}, {"ECH", 0}, {"PAS", 0}, {"HH", 0}, {"RCH", 0},
    {"DWE", 0}, {"CPH", 0}, {"LHI", 0}, {"BMH", 0}, {"OPT", 0}, {"EV1", 0},
    {"EV2", 0}, {"EV3", 0}, {"PHYS", 0}, {"B1", 0}, {"B2", 0}, {"EIT", 0},
    {"ESC", 0}, {"C2", 0}, {"MC", 0}, {"DC", 0}
};

inline bool isGym(std::string squareName){
    for (int i = 22; i < 24; i++){
        if (OWNABLE[i][0] == squareName) {
            return true;
        }
    }
    return false;
}

inline bool isResidence(std::string squareName){
    for (int i = 24; i < 28; i++){
        if (OWNABLE[i][0] == squareName){
	    return true;
	}
    }
    return false;
}


inline bool isAcademic(std::string squareName){
    for (int i = 0; i < 22; i++){
        if (OWNABLE[i][0] == squareName){
	    return true;
	}
    }
    return false;
}


#endif
