#pragma once

#include <cstdint>

enum class FileMode
{
	Append = (1 << 0),
	ReadOnly = (1 << 1),
	Binary = (1 << 2),
	Failed = (1 << 3),
	Uninitialised = (1 << 4),
	
	Ascii = 0,
	OverWrite = 0,
	ReadWrite = 0,
};

namespace Disk
{
	FileMode open(char *, char);
	void close(void);
	char getChar(void);
	void putChar(char);
	void writeBytes(uint8_t *, uint16_t);
	uint16_t readBytes(uint8_t *, uint16_t);
	void seekAsbolute(long);
	void seekRelative(long);
	void rewind(void);
	void end(void);
	long getPosition(void);
	void setPosition(long);
	uint8_t peek(long);
	void poke(long, uint8_t);
	int readLine(char *, int);
	char * getCurrentFileName(void);
	char * getNextFile(char*);
	char * getNextFile(void);
	char * getFirstFile(char*);
	char * getFirstFile(void);
	char * getFirstDirEntry(void);
	char * getNextDirEntry(void);	
	int isThisFileOpen(char*);
	int fileOk(void);
	int dirOpen(void);
	int dirUp(void);
}