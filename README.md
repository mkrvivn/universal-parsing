# universal-parsing [study project]
<h2> Installation </h2>

build with tests:  

```
git clone https://github.com/mkrvivn/universal-parsing.git --recusive
cd universal-parsing
mkdir build
cd build 
cmake -D BUILD_TESTS=ON ..
make
```


build without tests:  
```
git clone https://github.com/mkrvivn/universal-parsing.git
cd universal-parsing
mkdir build
cd build 
cmake ..
make
```

<h2>Usage example</h2>

```cpp
#include "Serializer.h"
#include "BencodeParser.h"
#include <iostream>
int main()
{
  std::string bencode = "d3:bar4:spam3:fooi42ee";
  auto o = parser::BencodeParser::parse(bencode);
  std::cout << o.encode<parser::BencodeParser>() << std::endl;
  //d3:bar4:spam3:fooi42ee
  std::string bar = o["bar"];
  std::cout << bar << std::endl;
  //spam
  return 0;
}

```

[more examples](https://github.com/mkrvivn/universal-parsing/tree/main/tests)

<h2>Future work</h2>

- [ ] Add typed get functions
- [ ] Add functionality to containers
- [ ] Add ordered map
- [ ] Add ordering policy
- [ ] Add templated GET request parser
- [ ] Add form-data parser
