#ifndef __FACEDB_HPP__
#define __FACEDB_HPP__

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "sqlite3.h"

typedef int (*sqlite_callback)(void* para,int columnCount,char** columnValue,char** columnName);


class facedb
{

public:
	facedb();
	~facedb();
	int FaceDb_Open(const char* filename,sqlite3 **ppDb);
	int FaceDb_Close(sqlite3 *pDb);

	int Facedb_Createtable(sqlite3 *pDb,const char* tablename,char** zErrMsg);
	int Facedb_Createtable(sqlite3 *pDb,char* psql,char** zErrMsg);

	int FaceDb_Insert(sqlite3 *pDb,sqlite3_stmt *stmt,const char*tablename,int userid,const char* username,char* pbuf,int nbytes);
	int FaceDb_Insert(sqlite3 *pDb,sqlite3_stmt *stmt,char* psql,char* pbuf,int nbytes);
	

	int FaceDb_Delete(sqlite3 *pDb,char* psql,char** zErrMsg);
	int FaceDb_Delete(sqlite3 *pDb,const char* tablename,int userid,char** zErrMsg);
	int FaceDb_Delete(sqlite3 *pDb,const char* tablename,const char* usrname,char** zErrMsg);
	int FaceDb_Delete(sqlite3 *pDb,const char* tablename,char** zErrMsg);
	
	int FaceDb_UpdataIDbyname(sqlite3 *pDb,const char* tablename,const char* usrname,int userid,char** zErrMsg);
	int FaceDb_UpdatanamebyID(sqlite3 *pDb,const char* tablename,const char* usrname,int userid,char** zErrMsg);
	int FaceDb_Update_feature(sqlite3 *pDb,const char* tablename,int userid,char* pbuf,int nBytes,char** zErrMsg);
	int FaceDb_Update_feature(sqlite3 *pDb,const char* tablename,const char* usrname,char* pbuf,int nBytes,char** zErrMsg);

	int FaceDb_SearchIDbyname(sqlite3 *pDb,sqlite3_stmt *stmt,const char* tablename,const char* username,int* ID);
	int FaceDb_SearchnamebyID(sqlite3 *pDb,sqlite3_stmt *stmt,const char* tablename,int userid,char* username);
	int FaceDb_SearchfeaturebyID(sqlite3 *pDb,sqlite3_stmt *stmt,const char* tablename,int userid,char* pbuf,int* buflen);
	int FaceDb_Searchfeaturebyname(sqlite3 *pDb,sqlite3_stmt *stmt,const char* tablename,const char* username,char* pbuf,int* buflen);
	int FaceDb_Search(sqlite3 *pDb,sqlite3_stmt *stmt,const char* tablename,const char* username,int userid,char* pbuf,int* buflen);

	int Getcount(sqlite3 *pDb,sqlite3_stmt *stmt,const char* tablename);

private:
	sqlite3 *FaceDb;
	sqlite3_stmt *stmt;	
	char sql[512];
};


	

#endif