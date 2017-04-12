
#include<vector>
#include"Network_types.h"

typedef Delinquent_network::Delinquent   Delinquent;

int main( void )
{
//  Delinquent_network network("../Data_sets/Test/test.txt");
  Delinquent_network network("../Data_sets/Medici/m_network.txt");

  std::vector<Delinquent> path;
  Delinquent from,  to;
  int sr1, sr2;
  
 // network.export_as_txt();
  
//////////////////////////////////////////////////////////////////////////////////////

//  network.construct_possible_path_with_different_methods(13,4);
  

  std::cout << " ********************************************************** " << std::endl;
  std::cout << " The greedy-deterministic method yields the following results: " << std::endl << std::endl;


  std::vector<int> or_path;

  //////////////////
  
  sr1=9;
  sr2=48; 


  from = network.delinquent_from_serial(sr1);
  to = network.delinquent_from_serial(sr2);

  std::cout<< " From " << from.name << " to " << to.name << " :   "; 

  network.construct_greedy_capacity_path( network.serial_to_node_index(sr1),
                                          network.serial_to_node_index(sr2), 
                                          std::back_inserter(path));
  network.print_path(path);



  path.clear();


  //////////////////
  
  sr1=10;
  sr2=20; 

  from = network.delinquent_from_serial(sr1);
  to = network.delinquent_from_serial(sr2);

  std::cout<< " From " << from.name << " to " << to.name << " :   "; 

  network.construct_greedy_capacity_path( network.serial_to_node_index(sr1),
                                          network.serial_to_node_index(sr2), 
                                          std::back_inserter(path));
  network.print_path(path);
  path.clear();


  //////////////////
  
  
  sr1=13;
  sr2=1; 

  from = network.delinquent_from_serial(sr1);
  to = network.delinquent_from_serial(sr2);

  std::cout<< " From " << from.name << " to " << to.name << " :   "; 

  network.construct_greedy_capacity_path( network.serial_to_node_index(sr1),
                                          network.serial_to_node_index(sr2), 
                                          std::back_inserter(path));
  network.print_path(path);
  path.clear();


  //////////////////
  
  sr1=13;
  sr2=21; 

  from = network.delinquent_from_serial(sr1);
  to = network.delinquent_from_serial(sr2);

  std::cout<< " From " << from.name << " to " << to.name << " :   "; 

  network.construct_greedy_capacity_path( network.serial_to_node_index(sr1),
                                          network.serial_to_node_index(sr2), 
                                          std::back_inserter(path));
  network.print_path(path);
  path.clear();



  //////////////////
  
  sr1=13;
  sr2=23; 

  from = network.delinquent_from_serial(sr1);
  to = network.delinquent_from_serial(sr2);

  std::cout<< " From " << from.name << " to " << to.name << " :   "; 

  network.construct_greedy_capacity_path( network.serial_to_node_index(sr1),
                                          network.serial_to_node_index(sr2), 
                                          std::back_inserter(path));
  network.print_path(path);
  path.clear();



  //////////////////
  
  sr1=13;
  sr2=24; 

  from = network.delinquent_from_serial(sr1);
  to = network.delinquent_from_serial(sr2);

  std::cout<< " From " << from.name << " to " << to.name << " :   "; 

  network.construct_greedy_capacity_path( network.serial_to_node_index(sr1),
                                          network.serial_to_node_index(sr2), 
                                          std::back_inserter(path));
  network.print_path(path);
  path.clear();


  //////////////////
  
  sr1=13;
  sr2=38; 

  from = network.delinquent_from_serial(sr1);
  to = network.delinquent_from_serial(sr2);

  std::cout<< " From " << from.name << " to " << to.name << " :   "; 

  network.construct_greedy_capacity_path( network.serial_to_node_index(sr1),
                                          network.serial_to_node_index(sr2), 
                                          std::back_inserter(path));
  network.print_path(path);
  path.clear();



  //////////////////
  
  sr1=13;
  sr2=51; 

  from = network.delinquent_from_serial(sr1);
  to = network.delinquent_from_serial(sr2);

  std::cout<< " From " << from.name << " to " << to.name << " :   "; 

  network.construct_greedy_capacity_path( network.serial_to_node_index(sr1),
                                          network.serial_to_node_index(sr2), 
                                          std::back_inserter(path));
  network.print_path(path);
  path.clear();


  //////////////////
  
  sr1=13;
  sr2=64; 

  from = network.delinquent_from_serial(sr1);
  to = network.delinquent_from_serial(sr2);

  std::cout<< " From " << from.name << " to " << to.name << " :   "; 

  network.construct_greedy_capacity_path( network.serial_to_node_index(sr1),
                                          network.serial_to_node_index(sr2), 
                                          std::back_inserter(path));
  network.print_path(path);
  path.clear();


  //////////////////
  
  sr1=13;
  sr2=92; 

  from = network.delinquent_from_serial(sr1);
  to = network.delinquent_from_serial(sr2);

  std::cout<< " From " << from.name << " to " << to.name << " :   "; 

  network.construct_greedy_capacity_path( network.serial_to_node_index(sr1),
                                          network.serial_to_node_index(sr2), 
                                          std::back_inserter(path));
  network.print_path(path);
  path.clear();


  //////////////////
  
  sr1=19;
  sr2=1; 

  from = network.delinquent_from_serial(sr1);
  to = network.delinquent_from_serial(sr2);

  std::cout<< " From " << from.name << " to " << to.name << " :   "; 

  network.construct_greedy_capacity_path( network.serial_to_node_index(sr1),
                                          network.serial_to_node_index(sr2), 
                                          std::back_inserter(path));
  network.print_path(path);
  path.clear();


  //////////////////
  
  sr1=19;
  sr2=11; 

  from = network.delinquent_from_serial(sr1);
  to = network.delinquent_from_serial(sr2);

  std::cout<< " From " << from.name << " to " << to.name << " :   "; 

  network.construct_greedy_capacity_path( network.serial_to_node_index(sr1),
                                          network.serial_to_node_index(sr2), 
                                          std::back_inserter(path));
  network.print_path(path);
  path.clear();


  //////////////////
  
  sr1=19;
  sr2=21; 

  from = network.delinquent_from_serial(sr1);
  to = network.delinquent_from_serial(sr2);

  std::cout<< " From " << from.name << " to " << to.name << " :   "; 

  network.construct_greedy_capacity_path( network.serial_to_node_index(sr1),
                                          network.serial_to_node_index(sr2), 
                                          std::back_inserter(path));
  network.print_path(path);
  path.clear();


  //////////////////
  
  sr1=19;
  sr2=92; 

  from = network.delinquent_from_serial(sr1);
  to = network.delinquent_from_serial(sr2);

  std::cout<< " From " << from.name << " to " << to.name << " :   "; 

  network.construct_greedy_capacity_path( network.serial_to_node_index(sr1),
                                          network.serial_to_node_index(sr2), 
                                          std::back_inserter(path));
  network.print_path(path);
  path.clear();


  //////////////////
  
  sr1=19;
  sr2=96; 

  from = network.delinquent_from_serial(sr1);
  to = network.delinquent_from_serial(sr2);

  std::cout<< " From " << from.name << " to " << to.name << " :   "; 

  network.construct_greedy_capacity_path( network.serial_to_node_index(sr1),
                                          network.serial_to_node_index(sr2), 
                                          std::back_inserter(path));
  network.print_path(path);
  path.clear();

  //////////////////
  
  sr1=23;
  sr2=21; 

  from = network.delinquent_from_serial(sr1);
  to = network.delinquent_from_serial(sr2);

  std::cout<< " From " << from.name << " to " << to.name << " :   "; 

  network.construct_greedy_capacity_path( network.serial_to_node_index(sr1),
                                          network.serial_to_node_index(sr2), 
                                          std::back_inserter(path));
  network.print_path(path);
  path.clear();

  //////////////////
  
  sr1=23;
  sr2=24; 

  from = network.delinquent_from_serial(sr1);
  to = network.delinquent_from_serial(sr2);

  std::cout<< " From " << from.name << " to " << to.name << " :   "; 

  network.construct_greedy_capacity_path( network.serial_to_node_index(sr1),
                                          network.serial_to_node_index(sr2), 
                                          std::back_inserter(path));
  network.print_path(path);
  path.clear();

  //////////////////
  
  sr1=48;
  sr2=92; 

  from = network.delinquent_from_serial(sr1);
  to = network.delinquent_from_serial(sr2);

  std::cout<< " From " << from.name << " to " << to.name << " :   "; 

  network.construct_greedy_capacity_path( network.serial_to_node_index(sr1),
                                          network.serial_to_node_index(sr2), 
                                          std::back_inserter(path));
  network.print_path(path);
  path.clear();




  std::cout << " ********************************************************** " << std::endl << std::endl << std::endl; 


  std::cout << " ********************************************************** " << std::endl;
  std::cout << " The maximum-arboresence method yields the following results: " << std::endl << std::endl;

  //////////////////
  
  sr1=9;
  sr2=48; 

  from = network.delinquent_from_serial(sr1);
  to = network.delinquent_from_serial(sr2);

  std::cout<< " From " << from.name << " to " << to.name << " :   "; 

  network.construct_path_via_maximum_arboresence( network.serial_to_node_index(sr1),
                                          network.serial_to_node_index(sr2), 
                                          std::back_inserter(path));
  network.print_path(path);
  path.clear();


  //////////////////
  
  sr1=10;
  sr2=20; 

  from = network.delinquent_from_serial(sr1);
  to = network.delinquent_from_serial(sr2);

  std::cout<< " From " << from.name << " to " << to.name << " :   "; 

  network.construct_path_via_maximum_arboresence( network.serial_to_node_index(sr1),
                                          network.serial_to_node_index(sr2), 
                                          std::back_inserter(path));
  network.print_path(path);
  path.clear();


  //////////////////
  
  
  sr1=13;
  sr2=1; 

  from = network.delinquent_from_serial(sr1);
  to = network.delinquent_from_serial(sr2);

  std::cout<< " From " << from.name << " to " << to.name << " :   "; 

  network.construct_path_via_maximum_arboresence( network.serial_to_node_index(sr1),
                                          network.serial_to_node_index(sr2), 
                                          std::back_inserter(path));
  network.print_path(path);
  path.clear();


  //////////////////
  
  sr1=13;
  sr2=21; 

  from = network.delinquent_from_serial(sr1);
  to = network.delinquent_from_serial(sr2);

  std::cout<< " From " << from.name << " to " << to.name << " :   "; 

  network.construct_path_via_maximum_arboresence( network.serial_to_node_index(sr1),
                                          network.serial_to_node_index(sr2), 
                                          std::back_inserter(path));
  network.print_path(path);
  path.clear();



  //////////////////
  
  sr1=13;
  sr2=23; 

  from = network.delinquent_from_serial(sr1);
  to = network.delinquent_from_serial(sr2);

  std::cout<< " From " << from.name << " to " << to.name << " :   "; 

  network.construct_path_via_maximum_arboresence( network.serial_to_node_index(sr1),
                                          network.serial_to_node_index(sr2), 
                                          std::back_inserter(path));
  network.print_path(path);
  path.clear();



  //////////////////
  
  sr1=13;
  sr2=24; 

  from = network.delinquent_from_serial(sr1);
  to = network.delinquent_from_serial(sr2);

  std::cout<< " From " << from.name << " to " << to.name << " :   "; 

  network.construct_path_via_maximum_arboresence( network.serial_to_node_index(sr1),
                                          network.serial_to_node_index(sr2), 
                                          std::back_inserter(path));
  network.print_path(path);
  path.clear();


  //////////////////
  
  sr1=13;
  sr2=38; 

  from = network.delinquent_from_serial(sr1);
  to = network.delinquent_from_serial(sr2);

  std::cout<< " From " << from.name << " to " << to.name << " :   "; 

  network.construct_path_via_maximum_arboresence( network.serial_to_node_index(sr1),
                                          network.serial_to_node_index(sr2), 
                                          std::back_inserter(path));
  network.print_path(path);
  path.clear();



  //////////////////
  
  sr1=13;
  sr2=51; 

  from = network.delinquent_from_serial(sr1);
  to = network.delinquent_from_serial(sr2);

  std::cout<< " From " << from.name << " to " << to.name << " :   "; 

  network.construct_path_via_maximum_arboresence( network.serial_to_node_index(sr1),
                                          network.serial_to_node_index(sr2), 
                                          std::back_inserter(path));
  network.print_path(path);
  path.clear();


  //////////////////
  
  sr1=13;
  sr2=64; 

  from = network.delinquent_from_serial(sr1);
  to = network.delinquent_from_serial(sr2);

  std::cout<< " From " << from.name << " to " << to.name << " :   "; 

  network.construct_path_via_maximum_arboresence( network.serial_to_node_index(sr1),
                                          network.serial_to_node_index(sr2), 
                                          std::back_inserter(path));
  network.print_path(path);
  path.clear();


  //////////////////
  
  sr1=13;
  sr2=92; 

  from = network.delinquent_from_serial(sr1);
  to = network.delinquent_from_serial(sr2);

  std::cout<< " From " << from.name << " to " << to.name << " :   "; 

  network.construct_path_via_maximum_arboresence( network.serial_to_node_index(sr1),
                                          network.serial_to_node_index(sr2), 
                                          std::back_inserter(path));
  network.print_path(path);
  path.clear();


  //////////////////
  
  sr1=19;
  sr2=1; 

  from = network.delinquent_from_serial(sr1);
  to = network.delinquent_from_serial(sr2);

  std::cout<< " From " << from.name << " to " << to.name << " :   "; 

  network.construct_path_via_maximum_arboresence( network.serial_to_node_index(sr1),
                                          network.serial_to_node_index(sr2), 
                                          std::back_inserter(path));
  network.print_path(path);
  path.clear();


  //////////////////
  
  sr1=19;
  sr2=11; 

  from = network.delinquent_from_serial(sr1);
  to = network.delinquent_from_serial(sr2);

  std::cout<< " From " << from.name << " to " << to.name << " :   "; 

  network.construct_path_via_maximum_arboresence( network.serial_to_node_index(sr1),
                                          network.serial_to_node_index(sr2), 
                                          std::back_inserter(path));
  network.print_path(path);
  path.clear();


  //////////////////
  
  sr1=19;
  sr2=21; 

  from = network.delinquent_from_serial(sr1);
  to = network.delinquent_from_serial(sr2);

  std::cout<< " From " << from.name << " to " << to.name << " :   "; 

  network.construct_path_via_maximum_arboresence( network.serial_to_node_index(sr1),
                                          network.serial_to_node_index(sr2), 
                                          std::back_inserter(path));
  network.print_path(path);
  path.clear();


  //////////////////
  
  sr1=19;
  sr2=92; 

  from = network.delinquent_from_serial(sr1);
  to = network.delinquent_from_serial(sr2);

  std::cout<< " From " << from.name << " to " << to.name << " :   "; 

  network.construct_path_via_maximum_arboresence( network.serial_to_node_index(sr1),
                                          network.serial_to_node_index(sr2), 
                                          std::back_inserter(path));
  network.print_path(path);
  path.clear();


  //////////////////
  
  sr1=19;
  sr2=96; 

  from = network.delinquent_from_serial(sr1);
  to = network.delinquent_from_serial(sr2);

  std::cout<< " From " << from.name << " to " << to.name << " :   "; 

  network.construct_path_via_maximum_arboresence( network.serial_to_node_index(sr1),
                                          network.serial_to_node_index(sr2), 
                                          std::back_inserter(path));
  network.print_path(path);
  path.clear();

  //////////////////
  
  sr1=23;
  sr2=21; 

  from = network.delinquent_from_serial(sr1);
  to = network.delinquent_from_serial(sr2);

  std::cout<< " From " << from.name << " to " << to.name << " :   "; 

  network.construct_path_via_maximum_arboresence( network.serial_to_node_index(sr1),
                                          network.serial_to_node_index(sr2), 
                                          std::back_inserter(path));
  network.print_path(path);
  path.clear();

  //////////////////
  
  sr1=23;
  sr2=24; 

  from = network.delinquent_from_serial(sr1);
  to = network.delinquent_from_serial(sr2);

  std::cout<< " From " << from.name << " to " << to.name << " :   "; 

  network.construct_path_via_maximum_arboresence( network.serial_to_node_index(sr1),
                                          network.serial_to_node_index(sr2), 
                                          std::back_inserter(path));
  network.print_path(path);
  path.clear();

  //////////////////
  
  sr1=48;
  sr2=92; 

  from = network.delinquent_from_serial(sr1);
  to = network.delinquent_from_serial(sr2);

  std::cout<< " From " << from.name << " to " << to.name << " :   "; 

  network.construct_path_via_maximum_arboresence( network.serial_to_node_index(sr1),
                                          network.serial_to_node_index(sr2), 
                                          std::back_inserter(path));
  network.print_path(path);
  path.clear();


  std::cout << " ********************************************************** " << std::endl << std::endl << std::endl;


  std::cout << " ********************************************************** " << std::endl;
  std::cout << " The shortest-path method yields the following results: " << std::endl << std::endl;

  bool unique_path;

  //////////////////
  
  sr1=9;
  sr2=48; 

  from = network.delinquent_from_serial(sr1);
  to = network.delinquent_from_serial(sr2);

  std::cout<< " From " << from.name << " to " << to.name << " :   "; 

  unique_path = network.construct_shortest_path( network.serial_to_node_index(sr1),
                                          network.serial_to_node_index(sr2), 
                                          std::back_inserter(path));
  if(unique_path)
    std::cout << "(Unique)  ";
  else
    std::cout << "( Not Unique)  ";


  network.print_path(path);
  path.clear();


  //////////////////
  
  sr1=10;
  sr2=20; 

  from = network.delinquent_from_serial(sr1);
  to = network.delinquent_from_serial(sr2);

  std::cout<< " From " << from.name << " to " << to.name << " :   "; 

  unique_path = network.construct_shortest_path( network.serial_to_node_index(sr1),
                                          network.serial_to_node_index(sr2), 
                                          std::back_inserter(path));
  if(unique_path)
    std::cout << "(Unique)  ";
  else
    std::cout << "( Not Unique)  ";


  network.print_path(path);
  path.clear();


  //////////////////
  
  sr1=13;
  sr2=1; 

  from = network.delinquent_from_serial(sr1);
  to = network.delinquent_from_serial(sr2);

  std::cout<< " From " << from.name << " to " << to.name << " :   "; 

  unique_path = network.construct_shortest_path( network.serial_to_node_index(sr1),
                                          network.serial_to_node_index(sr2), 
                                          std::back_inserter(path));
  if(unique_path)
    std::cout << "(Unique)  ";
  else
    std::cout << "( Not Unique)  ";


  network.print_path(path);
  path.clear();


  //////////////////
  
  sr1=13;
  sr2=21; 

  from = network.delinquent_from_serial(sr1);
  to = network.delinquent_from_serial(sr2);

  std::cout<< " From " << from.name << " to " << to.name << " :   "; 

  unique_path = network.construct_shortest_path( network.serial_to_node_index(sr1),
                                          network.serial_to_node_index(sr2), 
                                          std::back_inserter(path));
  if(unique_path)
    std::cout << "(Unique)  ";
  else
    std::cout << "( Not Unique)  ";


  network.print_path(path);
  path.clear();


  //////////////////
  
  sr1=13;
  sr2=23; 

  from = network.delinquent_from_serial(sr1);
  to = network.delinquent_from_serial(sr2);

  std::cout<< " From " << from.name << " to " << to.name << " :   "; 

  unique_path = network.construct_shortest_path( network.serial_to_node_index(sr1),
                                          network.serial_to_node_index(sr2), 
                                          std::back_inserter(path));
  if(unique_path)
    std::cout << "(Unique)  ";
  else
    std::cout << "( Not Unique)  ";


  network.print_path(path);
  path.clear();



  //////////////////
  
  sr1=13;
  sr2=24; 

  from = network.delinquent_from_serial(sr1);
  to = network.delinquent_from_serial(sr2);

  std::cout<< " From " << from.name << " to " << to.name << " :   "; 

  unique_path = network.construct_shortest_path( network.serial_to_node_index(sr1),
                                          network.serial_to_node_index(sr2), 
                                          std::back_inserter(path));
  if(unique_path)
    std::cout << "(Unique)  ";
  else
    std::cout << "( Not Unique)  ";


  network.print_path(path);
  path.clear();



  //////////////////
  
  sr1=13;
  sr2=38; 

  from = network.delinquent_from_serial(sr1);
  to = network.delinquent_from_serial(sr2);

  std::cout<< " From " << from.name << " to " << to.name << " :   "; 

  unique_path = network.construct_shortest_path( network.serial_to_node_index(sr1),
                                          network.serial_to_node_index(sr2), 
                                          std::back_inserter(path));
  if(unique_path)
    std::cout << "(Unique)  ";
  else
    std::cout << "( Not Unique)  ";


  network.print_path(path);
  path.clear();


  //////////////////
  
  sr1=13;
  sr2=51; 

  from = network.delinquent_from_serial(sr1);
  to = network.delinquent_from_serial(sr2);

  std::cout<< " From " << from.name << " to " << to.name << " :   "; 

  unique_path = network.construct_shortest_path( network.serial_to_node_index(sr1),
                                          network.serial_to_node_index(sr2), 
                                          std::back_inserter(path));
  if(unique_path)
    std::cout << "(Unique)  ";
  else
    std::cout << "( Not Unique)  ";


  network.print_path(path);
  path.clear();


  //////////////////
  
  sr1=13;
  sr2=64; 

  from = network.delinquent_from_serial(sr1);
  to = network.delinquent_from_serial(sr2);

  std::cout<< " From " << from.name << " to " << to.name << " :   "; 

  unique_path = network.construct_shortest_path( network.serial_to_node_index(sr1),
                                          network.serial_to_node_index(sr2), 
                                          std::back_inserter(path));
  if(unique_path)
    std::cout << "(Unique)  ";
  else
    std::cout << "( Not Unique)  ";


  network.print_path(path);
  path.clear();



  //////////////////
  
  sr1=13;
  sr2=92; 

  from = network.delinquent_from_serial(sr1);
  to = network.delinquent_from_serial(sr2);

  std::cout<< " From " << from.name << " to " << to.name << " :   "; 

  unique_path = network.construct_shortest_path( network.serial_to_node_index(sr1),
                                          network.serial_to_node_index(sr2), 
                                          std::back_inserter(path));
  if(unique_path)
    std::cout << "(Unique)  ";
  else
    std::cout << "( Not Unique)  ";


  network.print_path(path);
  path.clear();



  //////////////////
  
  sr1=19;
  sr2=1; 

  from = network.delinquent_from_serial(sr1);
  to = network.delinquent_from_serial(sr2);

  std::cout<< " From " << from.name << " to " << to.name << " :   "; 

  unique_path = network.construct_shortest_path( network.serial_to_node_index(sr1),
                                          network.serial_to_node_index(sr2), 
                                          std::back_inserter(path));
  if(unique_path)
    std::cout << "(Unique)  ";
  else
    std::cout << "( Not Unique)  ";


  network.print_path(path);
  path.clear();



  //////////////////
  
  sr1=19;
  sr2=11; 

  from = network.delinquent_from_serial(sr1);
  to = network.delinquent_from_serial(sr2);

  std::cout<< " From " << from.name << " to " << to.name << " :   "; 

  unique_path = network.construct_shortest_path( network.serial_to_node_index(sr1),
                                          network.serial_to_node_index(sr2), 
                                          std::back_inserter(path));
  if(unique_path)
    std::cout << "(Unique)  ";
  else
    std::cout << "( Not Unique)  ";


  network.print_path(path);
  path.clear();



  //////////////////
  
  sr1=19;
  sr2=21; 

  from = network.delinquent_from_serial(sr1);
  to = network.delinquent_from_serial(sr2);

  std::cout<< " From " << from.name << " to " << to.name << " :   "; 

  unique_path = network.construct_shortest_path( network.serial_to_node_index(sr1),
                                          network.serial_to_node_index(sr2), 
                                          std::back_inserter(path));
  if(unique_path)
    std::cout << "(Unique)  ";
  else
    std::cout << "( Not Unique)  ";


  network.print_path(path);
  path.clear();



  //////////////////
  
  sr1=19;
  sr2=92; 

  from = network.delinquent_from_serial(sr1);
  to = network.delinquent_from_serial(sr2);

  std::cout<< " From " << from.name << " to " << to.name << " :   "; 

  unique_path = network.construct_shortest_path( network.serial_to_node_index(sr1),
                                          network.serial_to_node_index(sr2), 
                                          std::back_inserter(path));
  if(unique_path)
    std::cout << "(Unique)  ";
  else
    std::cout << "( Not Unique)  ";


  network.print_path(path);
  path.clear();



  //////////////////
  
  sr1=19;
  sr2=96; 

  from = network.delinquent_from_serial(sr1);
  to = network.delinquent_from_serial(sr2);

  std::cout<< " From " << from.name << " to " << to.name << " :   "; 

  unique_path = network.construct_shortest_path( network.serial_to_node_index(sr1),
                                          network.serial_to_node_index(sr2), 
                                          std::back_inserter(path));
  if(unique_path)
    std::cout << "(Unique)  ";
  else
    std::cout << "( Not Unique)  ";


  network.print_path(path);
  path.clear();



  //////////////////
  
  sr1=23;
  sr2=21; 

  from = network.delinquent_from_serial(sr1);
  to = network.delinquent_from_serial(sr2);

  std::cout<< " From " << from.name << " to " << to.name << " :   "; 

  unique_path = network.construct_shortest_path( network.serial_to_node_index(sr1),
                                          network.serial_to_node_index(sr2), 
                                          std::back_inserter(path));
  if(unique_path)
    std::cout << "(Unique)  ";
  else
    std::cout << "( Not Unique)  ";


  network.print_path(path);
  path.clear();


  //////////////////
  
  sr1=23;
  sr2=24; 

  from = network.delinquent_from_serial(sr1);
  to = network.delinquent_from_serial(sr2);

  std::cout<< " From " << from.name << " to " << to.name << " :   "; 

  unique_path = network.construct_shortest_path( network.serial_to_node_index(sr1),
                                          network.serial_to_node_index(sr2), 
                                          std::back_inserter(path));
  if(unique_path)
    std::cout << "(Unique)  ";
  else
    std::cout << "( Not Unique)  ";


  network.print_path(path);
  path.clear();



  //////////////////
  
  sr1=48;
  sr2=92; 

  from = network.delinquent_from_serial(sr1);
  to = network.delinquent_from_serial(sr2);

  std::cout<< " From " << from.name << " to " << to.name << " :   "; 

  unique_path = network.construct_shortest_path( network.serial_to_node_index(sr1),
                                          network.serial_to_node_index(sr2), 
                                          std::back_inserter(path));
  if(unique_path)
    std::cout << "(Unique)  ";
  else
    std::cout << "( Not Unique)  ";


  network.print_path(path);
  path.clear();

  std::cout << " ********************************************************** " << std::endl << std::endl << std::endl;

  std::vector< std::vector<int> > actual_paths;


  sr1=9;
  sr2=48; 

  or_path.clear();
  or_path.push_back(9);
  or_path.push_back(93);
  or_path.push_back(19);
  or_path.push_back(48);

  actual_paths.push_back(or_path);

  or_path.clear();
  or_path.push_back(10);
  or_path.push_back(19);
  or_path.push_back(78);
  or_path.push_back(51);
  or_path.push_back(20);

  actual_paths.push_back(or_path);

  or_path.clear();
  or_path.push_back(13);
  or_path.push_back(19);
  or_path.push_back(24);
  or_path.push_back(1);

  actual_paths.push_back(or_path);

  or_path.clear();
  or_path.push_back(13);
  or_path.push_back(46);
  or_path.push_back(21);

  actual_paths.push_back(or_path);

  bool has1 = network.has_path(or_path);

  or_path.clear();
  or_path.push_back(13);
  or_path.push_back(19);
  or_path.push_back(21);

  actual_paths.push_back(or_path);

  or_path.clear();
  or_path.push_back(13);
  or_path.push_back(19);
  or_path.push_back(23);

  actual_paths.push_back(or_path);

  or_path.clear();
  or_path.push_back(13);
  or_path.push_back(19);
  or_path.push_back(24);

  actual_paths.push_back(or_path);

  or_path.clear();
  or_path.push_back(13);
  or_path.push_back(19);
  or_path.push_back(23);
  or_path.push_back(92);
  or_path.push_back(38);

  actual_paths.push_back(or_path);

  or_path.clear();
  or_path.push_back(13);
  or_path.push_back(19);
  or_path.push_back(23);
  or_path.push_back(51);

  actual_paths.push_back(or_path);

  or_path.clear();
  or_path.push_back(13);
  or_path.push_back(19);
  or_path.push_back(64);

  actual_paths.push_back(or_path);

  or_path.clear();
  or_path.push_back(13);
  or_path.push_back(19);
  or_path.push_back(2);
  or_path.push_back(92);

  actual_paths.push_back(or_path);

  or_path.clear();
  or_path.push_back(19);
  or_path.push_back(23);
  or_path.push_back(1);

  actual_paths.push_back(or_path);

  or_path.clear();
  or_path.push_back(19);
  or_path.push_back(26);
  or_path.push_back(11);

  actual_paths.push_back(or_path);

  or_path.clear();
  or_path.push_back(19);
  or_path.push_back(92);
  or_path.push_back(25);
  or_path.push_back(21);

  actual_paths.push_back(or_path);

  or_path.clear();
  or_path.push_back(19);
  or_path.push_back(48);
  or_path.push_back(92);

  actual_paths.push_back(or_path);

  or_path.clear();
  or_path.push_back(19);
  or_path.push_back(93);
  or_path.push_back(96);

  actual_paths.push_back(or_path);

  or_path.clear();
  or_path.push_back(23);
  or_path.push_back(19);
  or_path.push_back(21);

  actual_paths.push_back(or_path);

  or_path.clear();
  or_path.push_back(23);
  or_path.push_back(19);
  or_path.push_back(24);

  actual_paths.push_back(or_path);

  or_path.clear();
  or_path.push_back(48);
  or_path.push_back(19);
  or_path.push_back(23);
  or_path.push_back(92);

  actual_paths.push_back(or_path);

  std::cout << " Actual paths: " << std::endl << std::endl;

  for(int i=0; i<actual_paths.size(); i++)
    network.print_path(actual_paths[i]);

  std::cout << " ********************************************************** " << std::endl << std::endl << std::endl;

  std::cout << " Predictability of actual paths " << std::endl << std::endl ;

  for(int i=0; i<actual_paths.size(); i++)
    if(i!=3)
    {
      bool has = network.has_path(actual_paths[i]);

      int sr1 = actual_paths[i][0],
          sr2 = actual_paths[i].back();

      if(has)
        std::cout << " Actual path from: " << network.delinquent_from_serial(sr1).name 
                  << " to: " << network.delinquent_from_serial(sr2).name 
                  << " EXISTS in the modelled network. " << std::endl;
      else
        std::cout << " Actual path from: " << network.delinquent_from_serial(sr1).name 
                  << " to: " << network.delinquent_from_serial(sr2).name 
                  << " DOES NOT EXIST in the modelled network. " << std::endl;
    }
    else
    {
      int sr1 = actual_paths[3][0],
          sr2 = actual_paths[3].back();

        
      bool has1 = network.has_path(actual_paths[3]), 
           has2 = network.has_path(actual_paths[4]);

      std::cout << " From the two actual paths: " << network.delinquent_from_serial(sr1).name 
                << " to: " << network.delinquent_from_serial(sr2).name 
                << " there exist: " << int(has1)+int(has2) << " in the network ( A: "
                << has1 << " B: " << has2 << " ) "  << std::endl;

     

      i++;
    }

  //////////////////////////////////


//  network.export_as_txt();
//  network.export_as_Mathematica_code("../Data_sets/Test/test_new.data",true,true);
//  network.export_as_Mathematica_GraphPlot("../Data_sets/Test/test_plot.data",false,true);
//  network.export_as_Mathematica_code_undirected("../Data_sets/Test/test_new_undirected.data");

/////////////////////////////////////////////////////////////////////////////
//  Delinquent_network network("../Data_sets/Medici/m_network.txt");

//  network.export_as_txt();
 network.export_as_Mathematica_code("../Data_sets/Medici/m_network.data",true,true);
//  network.export_as_Mathematica_GraphPlot("../Data_sets/Medici/m_plot.data",false,true);
  network.export_as_Mathematica_code_undirected("../Data_sets/Medici/m_network_undirected.data");

  int ssr1 = network.serial_to_node_index(2),
      ssr2 = network.serial_to_node_index(21);

  Delinquent_network induced_subnetwork = network.extract_network_between_nodes(ssr1,ssr2);

  induced_subnetwork.export_as_Mathematica_code("../Data_sets/Medici/induced_subnetwork.data",true,true);

//////////////////////////////////////////////////////////////////////////////

//  Delinquent_network network_until_1980 = network.extract_network_at_period(1900,1980);
//  network_until_1980.export_as_Mathematica_code_undirected("../Data_sets/Medici/m_network_until_1980_undirected.data");

//  Delinquent_network network_1980_1990 = network.extract_network_at_period(1980,1990);
//  network_1980_1990.export_as_Mathematica_code_undirected("../Data_sets/Medici/m_network_1980_1990_undirected.data");

//  Delinquent_network network_since_1990 = network.extract_network_at_period(1990,2100);
//  network_since_1990.export_as_Mathematica_code_undirected("../Data_sets/Medici/m_network_since_1990_undirected.data");

  //////////////////////////////////////////////////////////////////////////

  std::vector< std::pair< Delinquent_network::Connection, double> > links1, links2;
  int num=30;

  network.predict_missing_links_Jaccard(num,std::back_inserter(links1));
  network.predict_missing_links_clique(num,std::back_inserter(links2));

  std::cout << std::endl << std::endl << " The average clustering coefficient of the network is: " 
                                      << network.average_clustering_coefficient()  << std::endl; 

  std::cout << " Number of nodes in the network: " << network.number_of_delinquents() << std::endl;

  bool sf = network.is_scale_free();

  if( sf == true )
    std::cout << std::endl << std::endl << " The network IS scale free " << std::endl;
  else
    std::cout << std::endl << std::endl << " The network is NOT scale free " << std::endl;

  std::cout << std::endl << std::endl << " The " << num << " most probable missing links according to" << std::endl
                                      << " the method that is based on the Jaccard coefficient are: " << std::endl;

  for( int i=0; i<links1.size(); i++ )
    std::cout << (network.delinquent(links1[i].first.from).name) << " <-> " 
              << (network.delinquent(links1[i].first.to).name) << "      Weight: " << links1[i].second 
              << std::endl << std::endl; 


  std::cout << std::endl << std::endl << " The " << num << " most probable missing links according to" << std::endl
                                      << " the method that is based on the clique assumption are: " << std::endl;

  for( int i=0; i<links2.size(); i++ )
    std::cout << (network.delinquent(links2[i].first.from).name) << " <-> " 
              << (network.delinquent(links2[i].first.to).name) << "      Weight: " << links2[i].second 
              << std::endl << std::endl;

 return 0;

}
