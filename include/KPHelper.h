#pragma once

#include <memory>
#include <string>
#include <exception>
#include <stdexcept>


#include <keepass/kdb.hh>
#include <keepass/kdbx.hh>
#include <keepass/key.hh>
#include <keepass/database.hh>
#include <keepass/group.hh>
#include <keepass/entry.hh>


class KPHelper
{
private:
	using DBptr = std::unique_ptr<keepass::Database>;
	using Gptr = std::shared_ptr<keepass::Group>;
	using Eptr = std::shared_ptr<keepass::Entry>;

	DBptr db;
	keepass::Key key;
	bool kdbx = false;

public:
	KPHelper(const std::string& pathstr, const std::string& keystr) : key(keystr)
	{
		std::ifstream f(pathstr);
		f.exceptions(f.failbit);
		f.close();

		std::size_t ext_delim = pathstr.rfind('.');
		if (ext_delim != std::string::npos && pathstr.substr(ext_delim, pathstr.length() - ext_delim) == ".kdbx")
			kdbx = true;

		if (kdbx)
		{
			keepass::KdbxFile file;
			db = file.Import(pathstr, key);
		}
		else
		{
			keepass::KdbFile file;
			db = file.Import(pathstr, key);
		}
	}
	~KPHelper() = default;


	Gptr findGroup(const std::string& path, char separator = '/')
	{
		std::size_t beg = 0;
		std::size_t end = std::string::npos;
		Gptr currptr = db->root();

		while ((end = path.find(separator, beg)) != std::string::npos)
		{
			currptr = findGroup(path.substr(beg, end-beg), currptr);
			beg = end + 1;
		}

		return findGroup(path.substr(beg), currptr);
	}

	Eptr findEntry(const std::string& path, char separator = '/')
	{
		std::size_t beg = 0;
		std::size_t end = std::string::npos;
		Gptr currptr = db->root();

		while ((end = path.find(separator, beg)) != std::string::npos)
		{
			currptr = findGroup(path.substr(beg, end - beg), currptr);
			beg = end + 1;
		}

		return findEntry(path.substr(beg), currptr);
	}

	//Gptr findGroup(const std::string& groupname)
	//{
	//	return findGroup(groupname, db->root());
	//}
	//
	//Eptr findEntry(const std::string& entryname)
	//{
	//	return findEntry(entryname, db->root());
	//}

	// STATIC TRASH, DO NOT TOUCH //

	static Gptr findGroup(const std::string& groupname, Gptr basegroup)
	{
		for (Gptr group : basegroup->Groups())
		{
			if (group->name() == groupname)
				return group;
		}
		throw std::invalid_argument("Could not find group of such name!");
	}

	static Eptr findEntry(const std::string& entryname, Gptr basegroup)
	{
		for (Eptr entry : basegroup->Entries())
		{
			if (entry->title().value() == entryname)
				return entry;
		}
		throw std::invalid_argument("Could not find entry of such name!");
	}
};
