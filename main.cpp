#include <iostream>
#include <unistd.h>
#include <getopt.h>
#include <iomanip>

using std::cout;
using std::endl;

void print_help() {
  std::cout <<
    "Usage:" << endl <<
    std::left << std::setw(20) << "--node_name -n:" << "Name of the serving ROS node, 'a1_node' by default" << endl <<
    std::left << std::setw(20) << "--mode -m:" << "Mode of A1 dog, sports(default) or basic" << endl <<
    "Example:" << endl <<
    "PATH_TO_CMD -m sports" << endl <<
    "PATH_TO_CMD --mode sports --node_name my_a1_node" << endl;
}

const char *get_arg(char *argv[]) {
  if (optarg != nullptr) {
    return optarg;
  }
  if (argv[optind] != nullptr) {
    return argv[optind];
  }

  print_help();
  exit(1);
}

// TODO It seems that the optional arguments with '=' are not working
// works: ./cmd --mode sports
// won't work: ./cmd --mode=sports, mode becomes '=sports', = is not handled
int main(int argc, char *argv[]) {
  //  Parse the commandline arguments
  const char *short_options = "m::n::";
  const option long_options[] = {
    {"mode", optional_argument, nullptr, 'm'},
    {"node_name", optional_argument, nullptr, 'n'}
  };

  std::string node_name = "a1_node";
  std::string mode = "sports";

  int opt;
  while ((opt = getopt_long(argc, argv, short_options, long_options, nullptr)) != -1) {
    switch (opt) {
      case 'm':
        mode = std::string(get_arg(argv));
        break;
      case 'n':
        node_name = std::string(get_arg(argv));
        break;

      default:
        break;
    }
  }
  cout << "running node [" << node_name << "] in {" << mode << "} mode" << endl;

  return 0;
}
