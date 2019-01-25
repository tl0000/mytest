#include "facedb.hpp"

#define _DEBUG_


facedb::facedb()
{

}

facedb::~facedb()
{

}

int facedb::FaceDb_Open(const char* filename,sqlite3 **ppDb)
{
	int ret;
	ret = sqlite3_open(filename, ppDb);
	return ret;
}

int facedb::FaceDb_Close(sqlite3 *pDb)
{
	int ret;
	ret = sqlite3_close(pDb);
	return ret;
}

int facedb::Facedb_Createtable(sqlite3 *pDb,const char* tablename,char** zErrMsg)
{
	char psql[128];
	sprintf(psql," CREATE TABLE %s(\
	NO INTEGER PRIMARY KEY,\
	UserID INTEGER,\
	Username TEXT(32),\
	Userfeature BLOB(1024)\
	);",tablename);

	#ifdef _DEBUG_

	printf("Createtable sql%s\n",psql );
	#endif

	int ret = sqlite3_exec(pDb , psql , NULL , NULL , zErrMsg ); 
	return ret;	
}

int facedb::Facedb_Createtable(sqlite3 *pDb,char* psql,char** zErrMsg)
{

	#ifdef _DEBUG_

	printf("Createtable sql%s\n",psql );
	#endif

	int ret = sqlite3_exec(pDb , psql , NULL , NULL , zErrMsg ); 
	return ret;	
}

int facedb::FaceDb_Insert(sqlite3 *pDb,sqlite3_stmt *stmt,const char* tablename,int userid,const char* username,char* pbuf,int nbytes)
{
	int ret;
	char psql[128];
 	sprintf(psql, "insert into %s values(NULL,%d,'%s',?)",tablename,userid,username); 
	ret = sqlite3_prepare(pDb, psql, strlen(psql), &stmt, NULL);    
	if (ret != SQLITE_OK) 
	{        
		fprintf(stderr, "db prepare fail, errcode[%d], errmsg[%s]\n", ret, sqlite3_errmsg(pDb));        
		sqlite3_close(pDb);        
		return -1;    
	}

 	ret = sqlite3_bind_blob(stmt, 1, pbuf, nbytes , NULL);    
 	if (ret != SQLITE_OK) 
 	{        
 		fprintf(stderr, "db bind fail, errcode[%d], errmsg[%s]\n", ret, sqlite3_errmsg(pDb));        
 		sqlite3_close(pDb);        
 		return -1;    
 	} 

 	ret = sqlite3_step(stmt);    
 	if (ret != SQLITE_DONE) 
 	{        
 		fprintf(stderr, "db insert fail, errcode[%d], errmsg[%s]\n", ret, sqlite3_errmsg(pDb));        
 		sqlite3_close(pDb);        
 		return -1;    
 	}     
 	sqlite3_finalize(stmt);
}

int facedb::FaceDb_Insert(sqlite3 *pDb,sqlite3_stmt *stmt,char* psql,char* pbuf,int nbytes)
{
	int ret;
 	   
	ret = sqlite3_prepare(pDb, psql, strlen(psql), &stmt, NULL);    
	if (ret != SQLITE_OK) 
	{        
		fprintf(stderr, "db prepare fail, errcode[%d], errmsg[%s]\n", ret, sqlite3_errmsg(pDb));        
		sqlite3_close(pDb);        
		return -1;    
	}

 	ret = sqlite3_bind_blob(stmt, 1, pbuf, nbytes , NULL);    
 	if (ret != SQLITE_OK) 
 	{        
 		fprintf(stderr, "db bind fail, errcode[%d], errmsg[%s]\n", ret, sqlite3_errmsg(pDb));        
 		sqlite3_close(pDb);        
 		return -1;    
 	} 

 	ret = sqlite3_step(stmt);    
 	if (ret != SQLITE_DONE) 
 	{        
 		fprintf(stderr, "db insert fail, errcode[%d], errmsg[%s]\n", ret, sqlite3_errmsg(pDb));        
 		sqlite3_close(pDb);        
 		return -1;    
 	}     
 	sqlite3_finalize(stmt);
}

int facedb::FaceDb_Delete(sqlite3 *pDb,char* psql,char** zErrMsg)
{
	sqlite3_exec( pDb , psql , NULL , NULL , zErrMsg );
}

int facedb::FaceDb_Delete(sqlite3 *pDb,const char* tablename,int userid,char** zErrMsg)
{
	char psql[128];
 	sprintf(psql,"DELETE FROM %s WHERE UserID = %d;",tablename,userid); 
	sqlite3_exec( pDb , psql , NULL , NULL , zErrMsg );
}

int facedb::FaceDb_Delete(sqlite3 *pDb,const char* tablename,const char* usrname,char** zErrMsg)
{
	char psql[128];
 	sprintf(psql,"DELETE FROM %s WHERE Username = '%s';",tablename,usrname); 
	sqlite3_exec( pDb , psql , NULL , NULL , zErrMsg );
}

int facedb::FaceDb_Delete(sqlite3 *pDb,const char* tablename,char** zErrMsg)
{
	char psql[128];
 	sprintf(psql,"DELETE FROM %s WHERE col is null ;",tablename); 
	sqlite3_exec( pDb , psql , NULL , NULL , zErrMsg );
}


int facedb::FaceDb_UpdataIDbyname(sqlite3 *pDb,const char* tablename,const char* usrname,int userid,char** zErrMsg)
{
	char psql[128];
	
 	sprintf(psql,"UPDATE %s SET UserID = %d WHERE Username = '%s';",tablename,userid,usrname); 
	sqlite3_exec( pDb , psql , NULL , NULL , zErrMsg );
}

int facedb::FaceDb_UpdatanamebyID(sqlite3 *pDb,const char* tablename,const char* usrname,int userid,char** zErrMsg)
{
	char psql[128];
	
 	sprintf(psql,"UPDATE %s SET Username = '%s' WHERE Userid = %d;",tablename,usrname,userid); 
	sqlite3_exec( pDb , psql , NULL , NULL ,zErrMsg);
}


int facedb::FaceDb_Update_feature(sqlite3 *pDb,const char* tablename,int userid,char* pbuf,int nBytes,char** zErrMsg)
{
	int ret;
	char psql[128];
 	sprintf(psql, "UPDATE %s SET  Userfeature = ? WHERE Userid = %d;",tablename,userid); 
	ret = sqlite3_prepare(pDb, psql, strlen(psql), &stmt, NULL);    
	if (ret != SQLITE_OK) 
	{        
		fprintf(stderr, "db prepare fail, errcode[%d], errmsg[%s]\n", ret, sqlite3_errmsg(pDb));        
		sqlite3_close(pDb);        
		return -1;    
	}

 	ret = sqlite3_bind_blob(stmt, 1, pbuf, nBytes , NULL);    
 	if (ret != SQLITE_OK) 
 	{        
 		fprintf(stderr, "db bind fail, errcode[%d], errmsg[%s]\n", ret, sqlite3_errmsg(pDb));        
 		sqlite3_close(pDb);        
 		return -1;    
 	} 

 	ret = sqlite3_step(stmt);    
 	if (ret != SQLITE_DONE) 
 	{        
 		fprintf(stderr, "db insert fail, errcode[%d], errmsg[%s]\n", ret, sqlite3_errmsg(pDb));        
 		sqlite3_close(pDb);        
 		return -1;    
 	}     
 	sqlite3_finalize(stmt);
 	return SQLITE_OK;
}

int facedb::FaceDb_Update_feature(sqlite3 *pDb,const char* tablename,const char* username,char* pbuf,int nBytes,char** zErrMsg)
{
	int ret;
	char psql[128];
 	sprintf(psql, "UPDATE %s SET  Userfeature = ? WHERE Username = '%s';",tablename,username); 
	ret = sqlite3_prepare(pDb, psql, strlen(psql), &stmt, NULL);    
	if (ret != SQLITE_OK) 
	{        
		fprintf(stderr, "db prepare fail, errcode[%d], errmsg[%s]\n", ret, sqlite3_errmsg(pDb));        
		sqlite3_close(pDb);        
		return -1;    
	}

 	ret = sqlite3_bind_blob(stmt, 1, pbuf, nBytes , NULL);    
 	if (ret != SQLITE_OK) 
 	{        
 		fprintf(stderr, "db bind fail, errcode[%d], errmsg[%s]\n", ret, sqlite3_errmsg(pDb));        
 		sqlite3_close(pDb);        
 		return -1;    
 	} 

 	ret = sqlite3_step(stmt);    
 	if (ret != SQLITE_DONE) 
 	{        
 		fprintf(stderr, "db insert fail, errcode[%d], errmsg[%s]\n", ret, sqlite3_errmsg(pDb));        
 		sqlite3_close(pDb);        
 		return -1;    
 	}     
 	sqlite3_finalize(stmt);
 	return SQLITE_OK;
}

int facedb::FaceDb_SearchIDbyname(sqlite3 *pDb,sqlite3_stmt *stmt,const char* tablename,const char* username,int* ID)
{
	int ret;
	char psql[128];

	sprintf(psql, "SELECT Userid FROM %s WHERE Username = '%s';",tablename,username);

	ret = sqlite3_prepare(pDb, psql, strlen(psql), &stmt, NULL);    
	if (ret != SQLITE_OK) 
	{        
		fprintf(stderr, "db prepare fail, errcode[%d], errmsg[%s]\n", ret, sqlite3_errmsg(pDb));        
		sqlite3_close(pDb);        
		return -1;    
	}     
      
	ret = sqlite3_step(stmt);        
	if (ret == SQLITE_ROW) 
	{            
		int id;                                    
		id = sqlite3_column_int(stmt, 0);  //ID
		*ID = id;
		
		#ifdef _DEBUG_

		printf("id = %d \n",id); 

		#endif 
	}

	else if (ret == SQLITE_DONE) 
	{            
		printf("select done!\n"); 
		return  SQLITE_DONE;         
	} 
	else 
	{            
		fprintf(stderr, "db step fail, errcode[%d], errmsg[%s]\n", ret, sqlite3_errmsg(pDb));  
		return ret;                 
	}   
	
	return SQLITE_OK;
}

int facedb::FaceDb_SearchnamebyID(sqlite3 *pDb,sqlite3_stmt *stmt,const char* tablename,int userid,char* username)
{
	int ret;
	char psql[128];

	sprintf(psql, "SELECT Username FROM %s WHERE Userid = %d;",tablename,userid);

	ret = sqlite3_prepare(pDb, psql, strlen(psql), &stmt, NULL);    
	if (ret != SQLITE_OK) 
	{        
		fprintf(stderr, "db prepare fail, errcode[%d], errmsg[%s]\n", ret, sqlite3_errmsg(pDb));        
		sqlite3_close(pDb);        
		return -1;    
	}     
       
	ret = sqlite3_step(stmt);        
	if (ret == SQLITE_ROW) 
	{           
		void *content = NULL; 
		int len;   

		content = (void *)sqlite3_column_text(stmt, 0); //name        
		len = sqlite3_column_bytes(stmt, 0);       

		memcpy(username,content,len);
		#ifdef _DEBUG_

		printf("len = %d ,username = %s\n",len,username); 

		#endif 
	}

	else if (ret == SQLITE_DONE) 
	{            
		printf("select done!\n"); 
		return  SQLITE_DONE;         
	} 
	else 
	{            
		fprintf(stderr, "db step fail, errcode[%d], errmsg[%s]\n", ret, sqlite3_errmsg(pDb));  
		return ret;                 
	}   
	return SQLITE_OK;
}

int facedb::FaceDb_SearchfeaturebyID(sqlite3 *pDb,sqlite3_stmt *stmt,const char* tablename,int userid,char* pbuf,int* buflen)
{
	int ret;
	char psql[128];
	sprintf(psql, "SELECT Userfeature FROM %s WHERE Userid = %d;",tablename,userid);
	ret = sqlite3_prepare(pDb, psql, strlen(psql), &stmt, NULL);    
	if (ret != SQLITE_OK) 
	{        
		fprintf(stderr, "db prepare fail, errcode[%d], errmsg[%s]\n", ret, sqlite3_errmsg(pDb));        
		sqlite3_close(pDb);        
		return -1;    
	}     
       
	ret = sqlite3_step(stmt);        
	if (ret == SQLITE_ROW) 
	{            
		int len;            
		void *content = NULL;             
		int feature[256];                             


		content = (void *)sqlite3_column_blob(stmt, 0);//feature            
		len = sqlite3_column_bytes(stmt, 0);            
		*buflen = len;
		memcpy(pbuf,content,len);
		
		#ifdef _DEBUG_

		for(int i=0;i<len;i++)
		{
			printf("%02X ", pbuf[i]);
		}  
		printf("\n");   
 
		#endif   
	} 
	else if (ret == SQLITE_DONE) 
	{            
		printf("select done!\n"); 
		return  SQLITE_DONE;         
	} 
	else 
	{            
		fprintf(stderr, "db step fail, errcode[%d], errmsg[%s]\n", ret, sqlite3_errmsg(pDb));  
		return ret;                 
	}   
	return SQLITE_OK;
}

int facedb::FaceDb_Searchfeaturebyname(sqlite3 *pDb,sqlite3_stmt *stmt,const char* tablename,const char* username,char* pbuf,int* buflen)
{
	int ret;
	char psql[128];
	sprintf(psql, "SELECT Userfeature FROM %s WHERE Username = '%s';",tablename,username);
	ret = sqlite3_prepare(pDb, psql, strlen(psql), &stmt, NULL);    
	if (ret != SQLITE_OK) 
	{        
		fprintf(stderr, "db prepare fail, errcode[%d], errmsg[%s]\n", ret, sqlite3_errmsg(pDb));        
		sqlite3_close(pDb);        
		return -1;    
	}     
       
	ret = sqlite3_step(stmt);        
	if (ret == SQLITE_ROW) 
	{            
		int len;            
		void *content = NULL;             
		int feature[256];                             


		content = (void *)sqlite3_column_blob(stmt, 0);//feature            
		len = sqlite3_column_bytes(stmt, 0);            
		*buflen = len;
		memcpy(pbuf,content,len);
		
		#ifdef _DEBUG_

		for(int i=0;i<len;i++)
		{
			printf("%02X ", pbuf[i]);
		}  
		printf("\n");   
 
		#endif   
	} 
	else if (ret == SQLITE_DONE) 
	{            
		printf("select done!\n"); 
		return  SQLITE_DONE;         
	} 
	else 
	{            
		fprintf(stderr, "db step fail, errcode[%d], errmsg[%s]\n", ret, sqlite3_errmsg(pDb));  
		return ret;                 
	}   
	return SQLITE_OK;
}

int facedb::FaceDb_Search(sqlite3 *pDb,sqlite3_stmt *stmt,const char* tablename,const char* username,int userid,char* pbuf,int* buflen)
{
	int ret;
	char psql[128];
	sprintf(psql, "SELECT Userfeature FROM %s WHERE Userid = %d AND Username = '%s';",tablename,userid,username);
	ret = sqlite3_prepare(pDb, psql, strlen(psql), &stmt, NULL);    
	if (ret != SQLITE_OK) 
	{        
		fprintf(stderr, "db prepare fail, errcode[%d], errmsg[%s]\n", ret, sqlite3_errmsg(pDb));        
		sqlite3_close(pDb);        
		return -1;    
	}     
       
	ret = sqlite3_step(stmt);        
	if (ret == SQLITE_ROW) 
	{            
		int len;            
		void *content = NULL;             
		int feature[256];                             


		content = (void *)sqlite3_column_blob(stmt, 0);//feature            
		len = sqlite3_column_bytes(stmt, 0);            
		*buflen = len;
		memcpy(pbuf,content,len);
		
		#ifdef _DEBUG_

		for(int i=0;i<len;i++)
		{
			printf("%02X ", pbuf[i]);
		}  
		printf("\n");   
 
		#endif   
	} 
	else if (ret == SQLITE_DONE) 
	{            
		printf("select done!\n"); 
		return  SQLITE_DONE;         
	} 
	else 
	{            
		fprintf(stderr, "db step fail, errcode[%d], errmsg[%s]\n", ret, sqlite3_errmsg(pDb));  
		return ret;                 
	}   
	return SQLITE_OK;
}

int facedb::Getcount(sqlite3 *pDb,sqlite3_stmt *stmt,const char* tablename)
{
	char psql[128];
	sprintf(psql, "SELECT count(*) FROM %s;",tablename);
    int ret = sqlite3_prepare(pDb, psql, strlen(psql), &stmt, NULL) ;
    if (ret != SQLITE_OK) 
	{        
		fprintf(stderr, "db prepare fail, errcode[%d], errmsg[%s]\n", ret, sqlite3_errmsg(pDb));        
		sqlite3_close(pDb);        
		return -1;    
	}     
 	ret = sqlite3_step(stmt);        
	if (ret == SQLITE_ROW) 
	{            
		int len;            
		void *content = NULL;             
		int feature[256];                             
        
		len = sqlite3_column_int(stmt, 0);            
		
		#ifdef _DEBUG_

		printf("%d ", len);

		printf("\n");   
 
		#endif   
	} 
	else if (ret == SQLITE_DONE) 
	{            
		printf("select done!\n"); 
		return  SQLITE_DONE;         
	} 
	else 
	{            
		fprintf(stderr, "db step fail, errcode[%d], errmsg[%s]\n", ret, sqlite3_errmsg(pDb));  
		return ret;                 
	}   
	return SQLITE_OK;
}
