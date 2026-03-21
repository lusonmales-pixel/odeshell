#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>

using namespace std;
namespace fs = std::filesystem;

void ls() {
  for (const auto &entry : fs::directory_iterator(fs::current_path())) {
    if (entry.is_directory()){
      cout << "[DIR]" << entry.path().filename().string() << endl;
    }
    else {
      cout << "[FILE]" << entry.path().filename().string() << endl;
    }
  }
}

void cd(const string &path) {
  try {
    fs::current_path(path);
  } catch (fs::filesystem_error &e) {
    cout << "Error: " << e.what() << " (＃＞＜)" << endl;
  }
}

void rm(const string &path) {
  try {
    fs::remove(path);
  } catch (fs::filesystem_error &e) {
    cout << "Error" << e.what() << " (＃＞＜)" << endl;
  }
}

void rmdir(const string &path) {
  try {
    fs::remove_all(path);
  } catch (fs::filesystem_error &e) {
    cout << "Error" << e.what() << " (＃＞＜)" << endl;
  }
}

void echo() {
  string msg;
  cout << "Enter text: ";
  getline(cin, msg);
  cout << "You said, " << msg << " (*^.^*)" << endl;
}

void clear() { system("clear"); }

void pwd() { cout << "Current path: " << fs::current_path() << endl; }

void touch(const string &name) { ofstream file(name); }

void mkdir(const string &name) { fs::create_directory(name); }

void help() {
  cout << "Hello! I am odeshell. U can check out all my commands here! \n1.ls "
          "- list of all files and directories \n2.cd - change directory "
          "\n3.rm - remove file/directory \n4.mkdir - create direcory \n5.echo "
          "- echos your text \n6.exit - end session \n7.rmdir - remove not "
          "empty directory \n8.touch - create file \n9.clear - clear terminal "
          "\10.pwd - print current path \11.run - run system commands(Example: "
          "run nano test.txt - open nano with file)"
       << endl;
}

void run(const char *command) { system(command); }

int main() {
  while (true) {
    string user_text;
    cout << "odeshell [" << fs::current_path().string() << "] >> ";
    getline(cin, user_text);

    // END SESSION
    if (user_text == "exit") {
      cout << "Bye, bye! (⌒‿⌒)";
      break;
    }

    // ECHO
    else if (user_text == "echo") {
      echo();
    }

    // CD
    else if (user_text == "cd") {
      cout << "Error! missing argument for cd (>[]<)";
    } else if (user_text.rfind("cd ", 0) == 0) {
      string path = user_text.substr(3);
      cd(path);
    }

    // RM
    else if (user_text == "rm") {
      cout << "Error! missing argument for rm (>[]<)";
    } else if (user_text.rfind("rm ", 0) == 0) {
      string path = user_text.substr(3);
      rm(path);
    }

    // MKDIR
    else if (user_text == "mkdir") {
      cout << "Error! missing argument for mkdir (>[]<)";
    } else if (user_text.rfind("mkdir", 0) == 0) {
      string path_name = user_text.substr(6);
      mkdir(path_name);
    }

    // RMDIR
    else if (user_text == "rmdir") {
      cout << "Error! missing argument for rmdir (>[]<)";
    } else if (user_text.rfind("rmdir", 0) == 0) {
      string path_name = user_text.substr(6);
      rmdir(path_name);
    }

    // TOUCH
    else if (user_text == "touch") {
      cout << "Error! missing argument for touch (>[]<)";
    } else if (user_text.rfind("touch", 0) == 0) {
      string file_name = user_text.substr(6);
      touch(file_name);
    }

    // LS
    else if (user_text == "ls") {
      ls();
    }

    // HELP
    else if (user_text == "help") {
      help();
    }

    // PWD
    else if (user_text == "pwd") {
      pwd();
    }

    // CLEAR
    else if (user_text == "clear") {
      clear();
    }

    // RUN
    else if (user_text.rfind("run ", 0) == 0) {
      string command = user_text.substr(4);
      run(command.c_str());
    }

    // FINAL ERROR HANDLER
    else {
      cout << "I don't know this command (＞﹏＜)" << endl;
    }
  }
}