#include <pebble.h>
#include <math.h>
#include <time.h>
#include "watchface.h"

// Define the elements
int elements_left = 0;
struct element elements[] = {
    { .name = "?", .code = "?", .number = "0", .mass = "?"},
    { .name = "Hydrogen", .code = "H", .number = "1", .mass= "1.00794", .element_group = other_non_metals},
    { .name = "Helium", .code = "He", .number = "2", .mass= "4.002602", .element_group = inert_gases},
    { .name = "Lithium", .code = "Li", .number = "3", .mass= "6.941", .element_group = alkali_metals},
    { .name = "Beryllium", .code = "Be", .number = "4", .mass= "9.01218", .element_group = alkaline_earth_metals},
    { .name = "Boron", .code = "B", .number = "5", .mass= "10.811", .element_group = other_non_metals},
    { .name = "Carbon", .code = "C", .number = "6", .mass= "12.011", .element_group = other_non_metals},
    { .name = "Nitrogen", .code = "N", .number = "7", .mass= "14.00674", .element_group = other_non_metals},
    { .name = "Oxygen", .code = "O", .number = "8", .mass= "15.9994", .element_group = other_non_metals},
    { .name = "Fluorine", .code = "F", .number = "9", .mass= "18.998403", .element_group = halogens},
    { .name = "Neon", .code = "Ne", .number = "10", .mass= "20.1797", .element_group = inert_gases},
    { .name = "Sodium", .code = "Na", .number = "11", .mass= "22.989768", .element_group = alkali_metals},
    { .name = "Magnesium", .code = "Mg", .number = "12", .mass= "24.305", .element_group = alkaline_earth_metals},
    { .name = "Aluminum", .code = "Al", .number = "13", .mass= "26.981539", .element_group = other_metals},
    { .name = "Silicon", .code = "Si", .number = "14", .mass= "28.0855", .element_group = other_non_metals},
    { .name = "Phosphorus", .code = "P", .number = "15", .mass= "30.973762", .element_group = other_non_metals},
    { .name = "Sulfur", .code = "S", .number = "16", .mass= "32.066", .element_group = other_non_metals},
    { .name = "Chlorine", .code = "Cl", .number = "17", .mass= "35.4527", .element_group = halogens},
    { .name = "Argon", .code = "Ar", .number = "18", .mass= "39.948", .element_group = inert_gases},
    { .name = "Potassium", .code = "K", .number = "19", .mass= "39.0983", .element_group = alkali_metals},
    { .name = "Calcium", .code = "Ca", .number = "20", .mass= "40.078", .element_group = alkaline_earth_metals},
    { .name = "Scandium", .code = "Sc", .number = "21", .mass= "44.95591", .element_group = transition_metals},
    { .name = "Titanium", .code = "Ti", .number = "22", .mass= "47.88", .element_group = transition_metals},
    { .name = "Vanadium", .code = "V", .number = "23", .mass= "50.9415", .element_group = transition_metals},
    { .name = "Chromium", .code = "Cr", .number = "24", .mass= "51.9961", .element_group = transition_metals},
    { .name = "Manganese", .code = "Mn", .number = "25", .mass= "54.93805", .element_group = transition_metals},
    { .name = "Iron", .code = "Fe", .number = "26", .mass= "55.847", .element_group = transition_metals},
    { .name = "Cobalt", .code = "Co", .number = "27", .mass= "58.9332", .element_group = transition_metals},
    { .name = "Nickel", .code = "Ni", .number = "28", .mass= "58.6934", .element_group = transition_metals},
    { .name = "Copper", .code = "Cu", .number = "29", .mass= "63.546", .element_group = transition_metals},
    { .name = "Zinc", .code = "Zn", .number = "30", .mass= "65.39", .element_group = transition_metals},
    { .name = "Gallium", .code = "Ga", .number = "31", .mass= "69.723", .element_group = other_metals},
    { .name = "Germanium", .code = "Ge", .number = "32", .mass= "72.61", .element_group = other_metals},
    { .name = "Arsenic", .code = "As", .number = "33", .mass= "74.92159", .element_group = other_non_metals},
    { .name = "Selenium", .code = "Se", .number = "34", .mass= "78.96", .element_group = other_non_metals},
    { .name = "Bromine", .code = "Br", .number = "35", .mass= "79.904", .element_group = halogens},
    { .name = "Krypton", .code = "Kr", .number = "36", .mass= "83.798", .element_group = inert_gases},
    { .name = "Rubidium", .code = "Rb", .number = "37", .mass= "85.4678", .element_group = alkali_metals},
    { .name = "Strontium", .code = "Sr", .number = "38", .mass= "87.62", .element_group = alkaline_earth_metals},
    { .name = "Yttrium", .code = "Y", .number = "39", .mass= "88.90585", .element_group = transition_metals},
    { .name = "Zirconium", .code = "Zr", .number = "40", .mass= "91.224", .element_group = transition_metals},
    { .name = "Niobium", .code = "Nb", .number = "41", .mass= "92.90638", .element_group = transition_metals},
    { .name = "Molybdenum", .code = "Mo", .number = "42", .mass= "95.94", .element_group = transition_metals},
    { .name = "Technetium", .code = "Tc", .number = "43", .mass= "97.9072", .element_group = transition_metals},
    { .name = "Ruthenium", .code = "Ru", .number = "44", .mass= "101.07", .element_group = transition_metals},
    { .name = "Rhodium", .code = "Rh", .number = "45", .mass= "102.9055", .element_group = transition_metals},
    { .name = "Palladium", .code = "Pd", .number = "46", .mass= "106.42", .element_group = transition_metals},
    { .name = "Silver", .code = "Ag", .number = "47", .mass= "107.8682", .element_group = transition_metals},
    { .name = "Cadmium", .code = "Cd", .number = "48", .mass= "112.411", .element_group = transition_metals},
    { .name = "Indium", .code = "In", .number = "49", .mass= "114.818", .element_group = other_metals},
    { .name = "Tin", .code = "Sn", .number = "50", .mass= "118.71", .element_group = other_metals},
    { .name = "Antimony", .code = "Sb", .number = "51", .mass= "121.76", .element_group = other_metals},
    { .name = "Tellurium", .code = "Te", .number = "52", .mass= "127.6", .element_group = other_non_metals},
    { .name = "Iodine", .code = "I", .number = "53", .mass= "126.90447", .element_group = halogens},
    { .name = "Xenon", .code = "Xe", .number = "54", .mass= "131.29", .element_group = inert_gases},
    { .name = "Cesium", .code = "Cs", .number = "55", .mass= "132.90543", .element_group = alkali_metals},
    { .name = "Barium", .code = "Ba", .number = "56", .mass= "137.327", .element_group = alkaline_earth_metals},
    { .name = "Lanthanum", .code = "La", .number = "57", .mass= "138.9055", .element_group = transition_metals},
    { .name = "Cerium", .code = "Ce", .number = "58", .mass= "140.115", .element_group = lanthanides},
    { .name = "Praseodymium", .code = "Pr", .number = "59", .mass= "140.90765", .element_group = lanthanides},
    { .name = "Neodymium", .code = "Nd", .number = "60", .mass= "144.24", .element_group = lanthanides},
    { .name = "Promethium", .code = "Pm", .number = "61", .mass= "144.9127", .element_group = lanthanides},
    { .name = "Samarium", .code = "Sm", .number = "62", .mass= "150.36", .element_group = lanthanides},
    { .name = "Europium", .code = "Eu", .number = "63", .mass= "151.965", .element_group = lanthanides},
    { .name = "Gadolinium", .code = "Gd", .number = "64", .mass= "157.25", .element_group = lanthanides},
    { .name = "Terbium", .code = "Tb", .number = "65", .mass= "158.92534", .element_group = lanthanides},
    { .name = "Dysprosium", .code = "Dy", .number = "66", .mass= "162.5", .element_group = lanthanides},
    { .name = "Holmium", .code = "Ho", .number = "67", .mass= "164.93032", .element_group = lanthanides},
    { .name = "Erbium", .code = "Er", .number = "68", .mass= "167.26", .element_group = lanthanides},
    { .name = "Thulium", .code = "Tm", .number = "69", .mass= "168.93421", .element_group = lanthanides},
    { .name = "Ytterbium", .code = "Yb", .number = "70", .mass= "173.04", .element_group = lanthanides},
    { .name = "Lutetium", .code = "Lu", .number = "71", .mass= "174.967", .element_group = lanthanides},
    { .name = "Hafnium", .code = "Hf", .number = "72", .mass= "178.49", .element_group = transition_metals},
    { .name = "Tantalum", .code = "Ta", .number = "73", .mass= "180.9479", .element_group = transition_metals},
    { .name = "Tungsten", .code = "W", .number = "74", .mass= "183.84", .element_group = transition_metals},
    { .name = "Rhenium", .code = "Re", .number = "75", .mass= "186.207", .element_group = transition_metals},
    { .name = "Osmium", .code = "Os", .number = "76", .mass= "190.23", .element_group = transition_metals},
    { .name = "Iridium", .code = "Ir", .number = "77", .mass= "192.22", .element_group = transition_metals},
    { .name = "Platinum", .code = "Pt", .number = "78", .mass= "195.08", .element_group = transition_metals},
    { .name = "Gold", .code = "Au", .number = "79", .mass= "196.96654", .element_group = transition_metals},
    { .name = "Mercury", .code = "Hg", .number = "80", .mass= "200.59", .element_group = transition_metals},
    { .name = "Thallium", .code = "Tl", .number = "81", .mass = "204.3833", .element_group = other_metals},
    { .name = "Lead", .code = "Pb", .number = "82", .mass = "207.2", .element_group = other_metals},
    { .name = "Bismuth", .code = "Bi", .number = "83", .mass = "208.98037", .element_group = other_metals},
    { .name = "Polonium", .code = "Po", .number = "84", .mass = "208.9824", .element_group = other_metals},
    { .name = "Astatine", .code = "At", .number = "85", .mass = "209.9871", .element_group = halogens},
    { .name = "Radon", .code = "Rn", .number = "86", .mass = "222.0176", .element_group = inert_gases},
    { .name = "Francium", .code = "Fr", .number = "87", .mass = "223.0197", .element_group = alkali_metals},
    { .name = "Radium", .code = "Ra", .number = "88", .mass = "226.0254", .element_group = alkaline_earth_metals},
    { .name = "Actinium", .code = "Ac", .number = "89", .mass = "227.0278", .element_group = transition_metals},
    { .name = "Thorium", .code = "Th", .number = "90", .mass = "232.0381", .element_group = actinides},
    { .name = "Protactinium", .code = "Pa", .number = "91", .mass = "231.03588", .element_group = actinides},
    { .name = "Uranium", .code = "U", .number = "92", .mass = "238.0289", .element_group = actinides},
    { .name = "Neptunium", .code = "Np", .number = "93", .mass = "237.048", .element_group = actinides},
    { .name = "Plutonium", .code = "Pu", .number = "94", .mass = "244.0642", .element_group = actinides},
    { .name = "Americium", .code = "Am", .number = "95", .mass = "243.0614", .element_group = actinides},
    { .name = "Curium", .code = "Cm", .number = "96", .mass = "247.0703", .element_group = actinides},
    { .name = "Berkelium", .code = "Bk", .number = "97", .mass = "247.0703", .element_group = actinides},
    { .name = "Californium", .code = "Cf", .number = "98", .mass = "251.0796", .element_group = actinides},
    { .name = "Einsteinium", .code = "Es", .number = "99", .mass = "252.083", .element_group = actinides},
    { .name = "Fermium", .code = "Fm", .number = "100", .mass = "257.0951", .element_group = actinides},
    { .name = "Mendelevium", .code = "Md", .number = "101", .mass = "258.1", .element_group = actinides},
    { .name = "Nobelium", .code = "No", .number = "102", .mass = "259.1009", .element_group = actinides},
    { .name = "Lawrencium", .code = "Lr", .number = "103", .mass = "262.11", .element_group = actinides},
    { .name = "Rutherfordium", .code = "Rf", .number = "104",  .mass = "261.109", .element_group = trans_actinides},
    { .name = "Dubnium", .code = "Db", .number = "105",  .mass = "262.114", .element_group = trans_actinides},
    { .name = "Seaborgium", .code = "Sg", .number = "106",  .mass = "266.122", .element_group = trans_actinides},
    { .name = "Bohrium", .code = "Bh", .number = "107",  .mass = "264.125", .element_group = trans_actinides},
    { .name = "Hassium", .code = "Hs", .number = "108",  .mass = "277", .element_group = trans_actinides},
    { .name = "Meitnerium", .code = "Mt", .number = "109",  .mass = "268.139", .element_group = trans_actinides},
    { .name = "Darmstadium", .code = "Ds", .number = "110", .mass = "281", .element_group = trans_actinides},
    { .name = "Roentgenium", .code = "Rg", .number = "111", .mass = "280", .element_group = trans_actinides},
    { .name = "Copernicium", .code = "Cn", .number = "112", .mass = "285", .element_group = trans_actinides},
    { .name = "Ununtrium", .code = "Uut", .number = "113", .mass = "284.000", .element_group = trans_actinides},
    { .name = "Flerovium", .code = "Fl", .number = "114", .mass = "289.000", .element_group = trans_actinides},
    { .name = "Ununpentium", .code = "Uup", .number = "115", .mass = "288.000", .element_group = trans_actinides},
    { .name = "Livermorium", .code = "Lv", .number = "116", .mass = "293.000", .element_group = trans_actinides},
    { .name = "Ununseptium", .code = "Uus", .number = "117", .mass = "294.000", .element_group = trans_actinides},
    { .name = "Ununoctium", .code = "Uuo", .number = "118", .mass = "294.000", .element_group = trans_actinides},
    { .name = "?", .code = "?", .number = "119", .mass = "?"},
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
    time_t temp = time(NULL);
    struct tm *tm = localtime(&temp);
    int element_number = 60 * (tm->tm_hour % 2) + tm->tm_min;

    if (element_number == 0 || element_number == 119) {
      // No matching element. Show the table summary
      show_spdf();
    }
    else {
      // Display the chosen element
      struct element new_element = elements[element_number];
      show_element(&new_element);
    }


    /*
    // If we did the whole table, start over
    if (elements_left == 0) {
        elements_left = number_of_elements;
    }

    // Select a random element
    int element_number = rand() % elements_left;
    struct element new_element = elements[element_number];

    // Push the selected element to the end of the table
    struct element last_element = elements[elements_left - 1];
    elements[elements_left - 1] = new_element;
    elements[element_number] = last_element;

    // Count down the number of elements left valid in the table
    elements_left -= 1;
    */
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
