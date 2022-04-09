#include <iostream>
#include <sstream>
#include "hashtable_open_addressing.h"

using std::cout;
using std::endl;

int main() {
    // Example test case in lab document
    // std::cout << "make an empty hash table with 11 buckets for strings" << std::endl;
    // HashTable<std::string> table(11);

    // std::cout << "initial size is " << table.size() << std::endl;
    // std::cout << "initial table size is " << table.table_size() << std::endl;

    // std::cout << "insert several strings" << std::endl;   
    // table.insert("And them who hold High Places");
    // table.insert("Must be the ones to start");
    // table.insert("To mold a new Reality");
    // // table.insert("Closer to the Heart");
    // table.insert("The Blacksmith and the Artist");
    // table.insert("Reflect it in their Art");
    // table.insert("Forge their Creativity");
    // // table.insert("Closer to the Heart");
    // table.insert("Philosophers and Plowmen");
    // table.insert("Each must know their Part");
    // table.insert("To sow a new Mentality");
    // // table.insert("Closer to the Heart");
    // table.insert("You can be the Captain");
    // table.insert("I will draw the Chart");
    // table.insert("Sailing into Destiny");
    // table.insert("Closer to the Heart");

    // table.insert("1");
    // table.insert("2");
    // table.insert("3");
    // table.insert("4");
    // table.insert("5");
    // table.insert("6");
    // table.insert("7");
    // table.insert("8");
    // table.insert("9");
    // table.insert("10");
    // table.insert("11");
    // table.insert("12");
    // table.insert("13");
    // table.insert("14");
    // table.insert("15");
    // table.insert("16");
    // table.insert("17");
    // table.insert("18");
    // table.insert("19");
    // table.insert("20");
    // table.insert("21");
    // table.insert("22");
    // table.insert("23");

    // std::cout << "size is " << table.size() << std::endl;
    // std::cout << "table size is " << table.table_size() << std::endl;

    // {
    // std::cout << "print the table" << std::endl;
    // std::stringstream ss;
    // table.print_table(ss);
    // std::cout << ss.str() << std::endl;
    // }

    // std::cout << "remove \"Philosophers and Plowmen\"" << std::endl;
    // table.remove("Philosophers and Plowmen");
    // std::cout << "remove \"Each must know their Part\"" << std::endl;
    // table.remove("Each must know their Part");

    // std::cout << "size is " << table.size() << std::endl;
    // std::cout << "table size is " << table.table_size() << std::endl;

    // {
    // std::cout << "print the table" << std::endl;
    // std::stringstream ss;
    // table.print_table(ss);
    // std::cout << ss.str() << std::endl;
    // }

    // std::cout << "find \"The Blacksmith and the Artist\"" << std::endl;
    // size_t index = table.position("The Blacksmith and the Artist");
    // std::cout << " ==> cell " << index << std::endl;

    // std::cout << "make the table empty" << std::endl;
    // table.make_empty();

    // std::cout << "size is " << table.size() << std::endl;
    // std::cout << "table size is " << table.table_size() << std::endl;

    // {
    // std::cout << "print the table" << std::endl;
    // std::stringstream ss;
    // table.print_table(ss);
    // std::cout << ss.str() << std::endl;
    // }

    HashTable<int> hash2;
    hash2.insert(0);
    hash2.insert(1);
    hash2.insert(2);
    hash2.insert(3);
    hash2.insert(4);
    hash2.insert(5);
    hash2.insert(6);
    hash2.insert(7);
    hash2.insert(8);
    hash2.insert(9);
    hash2.insert(10);
    hash2.insert(11);
    hash2.insert(12);
    hash2.insert(13);
    hash2.insert(14);
    hash2.insert(15);
    hash2.insert(16);
    hash2.insert(17);
    hash2.insert(18);
    hash2.insert(19);
    hash2.insert(20);
    hash2.insert(21);
    hash2.insert(22);
    hash2.insert(23);
    hash2.insert(24);
    hash2.insert(25);
    hash2.insert(26);
    hash2.insert(27);
    hash2.insert(28);
    hash2.insert(29);
    hash2.insert(30);
    hash2.insert(31);
    hash2.insert(32);
    hash2.insert(33);
    hash2.insert(34);
    hash2.insert(35);
    hash2.insert(36);
    hash2.insert(37);
    hash2.insert(38);
    hash2.insert(39);
    hash2.insert(40);
    hash2.insert(41);
    hash2.insert(42);
    hash2.insert(43);
    hash2.insert(44);
    hash2.insert(45);
    hash2.insert(46);
    hash2.insert(47);
    hash2.insert(48);
    hash2.insert(49);
    hash2.insert(50);
    hash2.insert(51);
    hash2.insert(52);
    hash2.insert(53);
    hash2.insert(54);
    hash2.insert(55);
    hash2.insert(56);
    hash2.insert(57);
    hash2.insert(58);
    hash2.insert(59);
    hash2.insert(60);
    hash2.insert(61);
    hash2.insert(62);
    hash2.insert(63);
    hash2.insert(64);
    hash2.insert(65);
    hash2.insert(66);
    hash2.insert(67);
    hash2.insert(68);
    hash2.insert(69);
    hash2.insert(70);
    hash2.insert(71);
    hash2.insert(72);
    hash2.insert(73);
    hash2.insert(74);
    hash2.insert(75);
    hash2.insert(76);
    hash2.insert(77);
    hash2.insert(78);
    hash2.insert(79);
    hash2.insert(80);
    hash2.insert(81);
    hash2.insert(82);
    hash2.insert(83);
    hash2.insert(84);
    hash2.insert(85);
    hash2.insert(86);
    hash2.insert(87);
    hash2.insert(88);
    hash2.insert(89);
    hash2.insert(90);
    hash2.insert(91);
    hash2.insert(92);
    hash2.insert(93);
    hash2.insert(94);
    hash2.insert(95);
    hash2.insert(96);
    hash2.insert(97);
    hash2.insert(98);
    hash2.insert(99);
    hash2.insert(100);

    HashTable<int> hash3(hash2);
    hash3.insert(101);
    hash3 = hash2;
    hash2.insert(102);
    hash3.insert(102);

    return 0;
}
