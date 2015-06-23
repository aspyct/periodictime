#include <pebble.h>
#include <math.h>
#include <time.h>
#include "watchface.h"

// Define the elements
int current_element = 0;
const int number_of_elements = 109;
const struct element elements[] = {
    { .name = "Hydrogen", .code = "H", .number = "1", .mass= "1.00794"},
    { .name = "Helium", .code = "He", .number = "2", .mass= "4.002602"},
    { .name = "Lithium", .code = "Li", .number = "3", .mass= "6.941"},
    { .name = "Beryllium", .code = "Be", .number = "4", .mass= "9.01218"},
    { .name = "Boron", .code = "B", .number = "5", .mass= "10.811"},
    { .name = "Carbon", .code = "C", .number = "6", .mass= "12.011"},
    { .name = "Nitrogen", .code = "N", .number = "7", .mass= "14.00674"},
    { .name = "Oxygen", .code = "O", .number = "8", .mass= "15.9994"},
    { .name = "Fluorine", .code = "F", .number = "9", .mass= "18.998403"},
    { .name = "Neon", .code = "Ne", .number = "10", .mass= "20.1797"},
    { .name = "Sodium", .code = "Na", .number = "11", .mass= "22.989768"},
    { .name = "Magnesium", .code = "Mg", .number = "12", .mass= "24.305"},
    { .name = "Aluminum", .code = "Al", .number = "13", .mass= "26.981539"},
    { .name = "Silicon", .code = "Si", .number = "14", .mass= "28.0855"},
    { .name = "Phosphorus", .code = "P", .number = "15", .mass= "30.973762"},
    { .name = "Sulfur", .code = "S", .number = "16", .mass= "32.066"},
    { .name = "Chlorine", .code = "Cl", .number = "17", .mass= "35.4527"},
    { .name = "Argon", .code = "Ar", .number = "18", .mass= "39.948"},
    { .name = "Potassium", .code = "K", .number = "19", .mass= "39.0983"},
    { .name = "Calcium", .code = "Ca", .number = "20", .mass= "40.078"},
    { .name = "Scandium", .code = "Sc", .number = "21", .mass= "44.95591"},
    { .name = "Titanium", .code = "Ti", .number = "22", .mass= "47.88"},
    { .name = "Vanadium", .code = "V", .number = "23", .mass= "50.9415"},
    { .name = "Chromium", .code = "Cr", .number = "24", .mass= "51.9961"},
    { .name = "Manganese", .code = "Mn", .number = "25", .mass= "54.93805"},
    { .name = "Iron", .code = "Fe", .number = "26", .mass= "55.847"},
    { .name = "Cobalt", .code = "Co", .number = "27", .mass= "58.9332"},
    { .name = "Nickel", .code = "Ni", .number = "28", .mass= "58.6934"},
    { .name = "Copper", .code = "Cu", .number = "29", .mass= "63.546"},
    { .name = "Zinc", .code = "Zn", .number = "30", .mass= "65.39"},
    { .name = "Gallium", .code = "Ga", .number = "31", .mass= "69.723"},
    { .name = "Germanium", .code = "Ge", .number = "32", .mass= "72.61"},
    { .name = "Arsenic", .code = "As", .number = "33", .mass= "74.92159"},
    { .name = "Selenium", .code = "Se", .number = "34", .mass= "78.96"},
    { .name = "Bromine", .code = "Br", .number = "35", .mass= "79.904"},
    { .name = "Krypton", .code = "Kr", .number = "36", .mass= "83.8"},
    { .name = "Rubidium", .code = "Rb", .number = "37", .mass= "85.4678"},
    { .name = "Strontium", .code = "Sr", .number = "38", .mass= "87.62"},
    { .name = "Yttrium", .code = "Y", .number = "39", .mass= "88.90585"},
    { .name = "Zirconium", .code = "Zr", .number = "40", .mass= "91.224"},
    { .name = "Niobium", .code = "Nb", .number = "41", .mass= "92.90638"},
    { .name = "Molybdenum", .code = "Mo", .number = "42", .mass= "95.94"},
    { .name = "Technetium", .code = "Tc", .number = "43", .mass= "97.9072"},
    { .name = "Ruthenium", .code = "Ru", .number = "44", .mass= "101.07"},
    { .name = "Rhodium", .code = "Rh", .number = "45", .mass= "102.9055"},
    { .name = "Palladium", .code = "Pd", .number = "46", .mass= "106.42"},
    { .name = "Silver", .code = "Ag", .number = "47", .mass= "107.8682"},
    { .name = "Cadmium", .code = "Cd", .number = "48", .mass= "112.411"},
    { .name = "Indium", .code = "In", .number = "49", .mass= "114.818"},
    { .name = "Tin", .code = "Sn", .number = "50", .mass= "118.71"},
    { .name = "Antimony", .code = "Sb", .number = "51", .mass= "121.76"},
    { .name = "Tellurium", .code = "Te", .number = "52", .mass= "127.6"},
    { .name = "Iodine", .code = "I", .number = "53", .mass= "126.90447"},
    { .name = "Xenon", .code = "Xe", .number = "54", .mass= "131.29"},
    { .name = "Cesium", .code = "Cs", .number = "55", .mass= "132.90543"},
    { .name = "Barium", .code = "Ba", .number = "56", .mass= "137.327"},
    { .name = "Lanthanum", .code = "La", .number = "57", .mass= "138.9055"},
    { .name = "Cerium", .code = "Ce", .number = "58", .mass= "140.115"},
    { .name = "Praseodymium", .code = "Pr", .number = "59", .mass= "140.90765"},
    { .name = "Neodymium", .code = "Nd", .number = "60", .mass= "144.24"},
    { .name = "Promethium", .code = "Pm", .number = "61", .mass= "144.9127"},
    { .name = "Samarium", .code = "Sm", .number = "62", .mass= "150.36"},
    { .name = "Europium", .code = "Eu", .number = "63", .mass= "151.965"},
    { .name = "Gadolinium", .code = "Gd", .number = "64", .mass= "157.25"},
    { .name = "Terbium", .code = "Tb", .number = "65", .mass= "158.92534"},
    { .name = "Dysprosium", .code = "Dy", .number = "66", .mass= "162.5"},
    { .name = "Holmium", .code = "Ho", .number = "67", .mass= "164.93032"},
    { .name = "Erbium", .code = "Er", .number = "68", .mass= "167.26"},
    { .name = "Thulium", .code = "Tm", .number = "69", .mass= "168.93421"},
    { .name = "Ytterbium", .code = "Yb", .number = "70", .mass= "173.04"},
    { .name = "Lutetium", .code = "Lu", .number = "71", .mass= "174.967"},
    { .name = "Hafnium", .code = "Hf", .number = "72", .mass= "178.49"},
    { .name = "Tantalum", .code = "Ta", .number = "73", .mass= "180.9479"},
    { .name = "Tungsten", .code = "W", .number = "74", .mass= "183.84"},
    { .name = "Rhenium", .code = "Re", .number = "75", .mass= "186.207"},
    { .name = "Osmium", .code = "Os", .number = "76", .mass= "190.23"},
    { .name = "Iridium", .code = "Ir", .number = "77", .mass= "192.22"},
    { .name = "Platinum", .code = "Pt", .number = "78", .mass= "195.08"},
    { .name = "Gold", .code = "Au", .number = "79", .mass= "196.96654"},
    { .name = "Mercury", .code = "Hg", .number = "80", .mass= "200.59"},
    { .name = "Thallium", .code = "Tl", .number = "81", .mass= "204.3833"},
    { .name = "Lead", .code = "Pb", .number = "82", .mass= "207.2"},
    { .name = "Bismuth", .code = "Bi", .number = "83", .mass= "208.98037"},
    { .name = "Polonium", .code = "Po", .number = "84", .mass= "208.9824"},
    { .name = "Astatine", .code = "At", .number = "85", .mass= "209.9871"},
    { .name = "Radon", .code = "Rn", .number = "86", .mass= "222.0176"},
    { .name = "Francium", .code = "Fr", .number = "87", .mass= "223.0197"},
    { .name = "Radium", .code = "Ra", .number = "88", .mass= "226.0254"},
    { .name = "Actinium", .code = "Ac", .number = "89", .mass= "227.0278"},
    { .name = "Thorium", .code = "Th", .number = "90", .mass= "232.0381"},
    { .name = "Protactinium", .code = "Pa", .number = "91", .mass= "231.03588"},
    { .name = "Uranium", .code = "U", .number = "92", .mass= "238.0289"},
    { .name = "Neptunium", .code = "Np", .number = "93", .mass= "237.048"},
    { .name = "Plutonium", .code = "Pu", .number = "94", .mass= "244.0642"},
    { .name = "Americium", .code = "Am", .number = "95", .mass= "243.0614"},
    { .name = "Curium", .code = "Cm", .number = "96", .mass= "247.0703"},
    { .name = "Berkelium", .code = "Bk", .number = "97", .mass= "247.0703"},
    { .name = "Californium", .code = "Cf", .number = "98", .mass= "251.0796"},
    { .name = "Einsteinium", .code = "Es", .number = "99", .mass= "252.083"},
    { .name = "Fermium", .code = "Fm", .number = "100", .mass= "257.0951"},
    { .name = "Mendelevium", .code = "Md", .number = "101", .mass= "258.1"},
    { .name = "Nobelium", .code = "No", .number = "102", .mass= "259.1009"},
    { .name = "Lawrencium", .code = "Lr", .number = "103", .mass= "262.11"},
    { .name = "Rutherfordium", .code = "Rf", .number = "104",  .mass= "[261]"},
    { .name = "Dubnium", .code = "Db", .number = "105",  .mass= "[262]"},
    { .name = "Seaborgium", .code = "Sg", .number = "106",  .mass= "[266]"},
    { .name = "Bohrium", .code = "Bh", .number = "107",  .mass= "[264]"},
    { .name = "Hassium", .code = "Hs", .number = "108",  .mass= "[269]"},
    { .name = "Meitnerium", .code = "Mt", .number = "109",  .mass= "[268]"}
};

static void update_time() {
  // Get a tm structure
  time_t temp = time(NULL); 
  struct tm *tick_time = localtime(&temp);

  // Create a long-lived buffer
  static char buffer[] = "00:00";

  // Write the current hours and minutes into the buffer
  if(clock_is_24h_style() == true) {
    // Use 24 hour format
    strftime(buffer, sizeof("00:00"), "%H:%M", tick_time);
  } else {
    // Use 12 hour format
    strftime(buffer, sizeof("00:00"), "%I:%M", tick_time);
  }

  // Display this time on the TextLayer
  set_time_label(buffer);
}

static void update_element() {
    // Choose a random element
    int element_number;
    
    do {
        element_number = rand() % number_of_elements;
    } while (element_number == current_element);
    
    current_element = element_number;
    set_element(elements + element_number);
}
    
static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
    update_time();
    update_element();
}
    
int main() {
    // Initialize random generator
    srand(time(NULL));
    
    show_watchface();
    update_element();
    
    // Register with TickTimerService
    tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
    
    // Run the event loop
    app_event_loop();
    
    // Bye bye :)
    return 0;
}