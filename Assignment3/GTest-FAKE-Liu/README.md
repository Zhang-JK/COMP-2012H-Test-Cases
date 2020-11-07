# 伪GTest for PA3

## 1. 声明：

使用此项目测评得到的结果不具有**任何参考价值**，**不可以**作为最终测评成绩以及Appeal的依据，仅用于**简单**测试自己的程序。

## 2. 缺陷：

由于如果对一些主要函数采用`GTest`，**有很大风险暴露代码**，因此对**以下函数不测评**：

（**欢迎`dalao`们补充剩余函数的测评~~~**）

- `Unit`的构造函数和析构函数(`Constructor & Destructor`) （5分）
- `Unit`中的`attack_unit()` （15分）
- `Unit Derived Class: Swordsman, Pikeman, Knight,Archer` （28分）
- `Memory leak`请自行使用`Valgrind`测评 （10分）

也就是，此项目仅会用`GTest`测评**共计42分**的内容。

而且，测评采用的地图及玩家信息比较简单，**不可能**包含所有情况，你也可以对`GTest.cpp`进行修改，以适应更复杂的数据。

## 3. 使用：

- 根据你的系统下载`Windows`版本或`MacOS`版本

- 将你的代码文件放在文件夹中，你的目录应该长成这个样子：

  - `GameEngine.h` (已有)
  - `GameEngine.cpp`
  - `GameMap.h` (已有)
  - `GameMap.cpp`
  - `Player.h` (已有)
  - `Player.cpp`
  - `Unit.h` (已有)
  - `Unit.cpp`
  - `Swordsman.h`
  - `Swordsman.cpp`
  - `Pikeman.h`
  - `Pikeman.cpp`
  - `Knight.h`
  - `Knight.cpp`
  - `Archer.h`
  - `Archer.cpp`
  - `no_print_map.cpp` (已有，这是测评辅助文件，不需更改)
  - `GTest.map` (已有，这是测评辅助文件，不需更改)
  - `GTest.player `(已有，这是测评辅助文件，不需更改)
  - `GTest.cpp` (已有，这是测评辅助文件，不需更改)
  - `\include`(已有，这是测评辅助文件，不需更改)
  - `\lib`(已有，这是测评辅助文件，不需更改)
  - `\googletest`(Windows下没有，这是测评辅助文件，不需更改)

- 打开`cmd`或终端，进入该文件夹（例如文件夹保存在桌面）

  Windows: `cd desktop/GTest-FAKE/Windows`

  MacOS: `cd desktop/GTest-FAKE/MacOS`

- 分别输入以下命令（建议每次输入一个命令）

  Windows:

  ```shell
  g++ -std=c++11 -pedantic -Wall -Wextra -g -c GameEngine.cpp -o GameEngine.o
  g++ -std=c++11 -pedantic -Wall -Wextra -g -c GameMap.cpp -o GameMap.o
  g++ -std=c++11 -pedantic -Wall -Wextra -g -c Player.cpp -o Player.o
  g++ -std=c++11 -pedantic -Wall -Wextra -g -c Unit.cpp -o Unit.o
  g++ -std=c++11 -pedantic -Wall -Wextra -g -c Swordsman.cpp -o Swordsman.o
  g++ -std=c++11 -pedantic -Wall -Wextra -g -c Pikeman.cpp -o Pikeman.o
  g++ -std=c++11 -pedantic -Wall -Wextra -g -c Knight.cpp -o Knight.o
  g++ -std=c++11 -pedantic -Wall -Wextra -g -c Archer.cpp -o Archer.o
  g++ -std=c++11 -pedantic -Wall -Wextra -g -c no_print_map.cpp -o no_print_map.o
  
  g++ -std=c++11 -pedantic -Wall -Wextra -g "-I.\\include" -c GTest.cpp -o GTest.o
  
  g++ "-L.\\lib" -o GTest.exe GameEngine.o  GameMap.o Player.o Unit.o Swordsman.o Pikeman.o Knight.o Archer.o GTest.o no_print_map.o -lgtest -lgtest_main
  
  GTest.exe
  
  ```

  MacOS:

  ```shell
  g++ -std=c++11 -pedantic -Wall -Wextra -g -c GameEngine.cpp -o GameEngine.o
  g++ -std=c++11 -pedantic -Wall -Wextra -g -c GameMap.cpp -o GameMap.o
  g++ -std=c++11 -pedantic -Wall -Wextra -g -c Player.cpp -o Player.o
  g++ -std=c++11 -pedantic -Wall -Wextra -g -c Unit.cpp -o Unit.o
  g++ -std=c++11 -pedantic -Wall -Wextra -g -c Swordsman.cpp -o Swordsman.o
  g++ -std=c++11 -pedantic -Wall -Wextra -g -c Pikeman.cpp -o Pikeman.o
  g++ -std=c++11 -pedantic -Wall -Wextra -g -c Knight.cpp -o Knight.o
  g++ -std=c++11 -pedantic -Wall -Wextra -g -c Archer.cpp -o Archer.o
  g++ -std=c++11 -pedantic -Wall -Wextra -g -c no_print_map.cpp -o no_print_map.o
  
  g++ -std=c++11 -pedantic -Wall -Wextra -g "-I./include" -c GTest.cpp -o GTest.o
  
  g++ "-L./lib" -o GTest GameEngine.o  GameMap.o Player.o Unit.o Swordsman.o Pikeman.o Knight.o Archer.o GTest.o no_print_map.o -lgtest -lgtest_main
  
  ./GTest
  ```

  **注意：**在文件编译过程中可能会出现多个`Warning`，你需要根据提示信息判断是否是自己程序出错（尽管你的程序没错，也可能会有`Warning`，可以直接忽略）；如果出现`error`，请检查你自己的程序能否在正常情况下通过编译。

  

  如果运行过程中出现了其他神奇的错误，请参考[`PA1 Grading Scheme & Appeal Procedure`](https://course.cse.ust.hk/comp2012h/assignments/pa1/grading.html#cases)，千万别问我，我是真的不会啊！X_X

## 4.不要忘了用`Valgrind`查看内存泄漏情况

- 这里不给出`Windows`下`Valgrind`的安装方法（欢迎补充！！）

- 如果你使用高版本的`MacOS`系统（即`Valgrind`官网不支持的系统），可以通过以下方式安装`Valgrind`

  ```shell
  brew remove valgrind   # only if you've installed it before
  
  brew tap LouisBrunner/valgrind
  
  brew install --HEAD LouisBrunner/valgrind/valgrind
  
  valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --undef-value-errors=no  ./GTest
  
  ```

  