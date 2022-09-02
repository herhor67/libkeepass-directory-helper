# libkeepass-directory-helper
This project is a simple header-only helper to [kindahl/libkeepass](https://github.com/kindahl/libkeepass).

Its purpose is to make file reading even simpler, and to implement traversing of group/entry trees by name/title.

Any other ideas or changes, please isssue.


# Using
The main entry point is the *KPHelper* class. It takes care of creating a key, choosing version, importing, and traversing the tree.

# Examples:
```cpp
	std::string path = "credentials.kdbx";
	std::string pass = "SuperSeretPaword";

	KPHelper KP(path, pass);

	std::string api_key = KP.findEntry("external/whatever/api_key")->password();
  
//	curl ...
```

```cpp
	std::string path = "credentials.kdbx";
	std::string pass = "SuperSeretPaword";

	KPHelper KP(path, pass);

	auto entry_ptr = KP.findEntry("external/database/mysql");
  
//	mysql_connect("localhost:3306", entry_ptr->username(), entry_ptr->password(), "table");
//	...
```
