# libkeepass-directory-helper
This project is a simple header-only helper to [kindahl/libkeepass](https://github.com/kindahl/libkeepass).

Its purpose is to make file reading even simpler, and to implement traversal of group/entry trees by name/title.

Any other ideas or changes, please issue.


# Using
The main entry point is the *KPHelper* class. It takes care of creating a key, choosing version, importing, and traversing the tree.


# Examples

Create helper, read file with pasword, read some api key to `std::string`.
```cpp
	std::string path = "credentials.kdbx";
	std::string pass = "SuperSeretPaword";

	KPHelper KP(path, pass);

	std::string api_key = KP.findEntry("external/whatever/api_key")->password();
  
//	curl ...
```

Get a pointer to some entry, then use `username()` and `password()` directly.
```cpp
	auto entry_ptr = KP.findEntry("internal/databases/mysql");
  
//	mysql_connect("localhost:3306", entry_ptr->username(), entry_ptr->password(), "my_schema");
//	...
```

Empty group names are skipped, the traverser stays in the same branch.
```cpp
	// Get root group
	auto root_ptr1 = KP.findGroup("");
	auto root_ptr2 = KP.findGroup("/");
	auto root_ptr3 = KP.findGroup("//////////");

	// Get some entry
	auto entry_ptr1 = KP.findEntry("some/arbitrary/path/to/entry");
	auto entry_ptr2 = KP.findEntry("/some/arbitrary/path/to/entry");
	auto entry_ptr3 = KP.findEntry("///some//arbitrary/path/////to//entry");
```
