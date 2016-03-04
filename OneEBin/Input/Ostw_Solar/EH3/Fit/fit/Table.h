#ifndef _TABLE_H_
#define _TABLE_H_

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>

class Table  {
 public:
  Table() {};

  Table( std::string filename )
    {  Open( filename );  };

  ~Table() {};

  /// opennnnnnnnnnnnnnnnnnnnnnnnn
  /// ############################
  int Open( std::string filename )
  {
    FileName = filename;
    NRows = 0;
    /// Open the file
    mTableFile.open( FileName.c_str(), std::ifstream::in );
    if( !mTableFile.is_open() )  {
      std::cout<< FileName <<" not open."<<std::endl;
      return 0;
    }

    /// Parse the lines
    std::string line;
    while( std::getline( mTableFile, line ) )  {
      // Catch comments / header                                                                                                                                  
      if( line.size()>0 && line[0]=='#' )  {
	Comments.push_back( line );

	if( line.size()>3 && line[1]==' ' && line[2]=='[' )  {
	  // Found header
	  HeaderLine = line;

	  // Parse header
	  std::string word;
	  std::istringstream iss(line, std::istringstream::in);
	  while( iss >> word )  {
	    if( word.length() > 1 )  {
	      std::string field = word.substr( 1, word.length()-2 );
	      FieldNames.push_back( field );
	      Columns[ field ].clear();
	      //std::cout<<word<<" ";
	    }
	  }
	} 
      } else {
	// Data line
	std::string word;
	std::istringstream iss(line, std::istringstream::in);
	unsigned int counter = 0;
	while( iss >> word )  {
	  Columns[ FieldNames[ counter ] ].push_back( word );
	  //std::cout<<word<<" ";
	  counter+=1;
	}
	
	// Insufficient data line
	if( counter < FieldNames.size() )   {
	  std::string zero("0");
	  //std::cout<<" Insufficient data line "<<std::endl;
	  for( unsigned int fill = counter; fill<FieldNames.size(); fill++ )   {
	    Columns[ FieldNames[ fill ] ].push_back( zero );
	  }
	}
	
	NRows += 1;
      }
      //std::cout<<std::endl;
    }

    return 1;
  }; 

  /// Writtttttttttttttttttttttttte
  /// #############################
  int Write( std::string filename )
  {
    /// Open the file
    FILE* Outfile = fopen(filename.c_str(), "w+");

    /// Output header
    std::vector< std::string >::iterator it, it_end = FieldNames.end();
    
    fprintf( Outfile, "# " );
    for( it=FieldNames.begin(); it!=it_end; it++ )   {
      fprintf( Outfile, "[" );
      fprintf( Outfile, "%s", (*it).c_str() );
      fprintf( Outfile, "] " );
    }
    fprintf( Outfile, "\n" );
    
    /// Output each row
    for( int row=0; row<NRows; row++ )   {
      for( it=FieldNames.begin(); it!=it_end; it++ )   {
	fprintf( Outfile, "%10s", Columns[(*it)][row].c_str() );
	fprintf( Outfile, "  " );
      }
      fprintf( Outfile, "\n" );
    }

    fclose( Outfile );
    return 1;
  }

 public:
  std::string                     FileName;      // Table file name
  std::vector< std::string >      Comments;      // All lines start with '#'
  std::string                     HeaderLine;    // The line with  '# [name1]  [name2] ...'. Position 0,1,2 must be '# ['
  std::vector< std::string >      FieldNames;    // Column names
  std::map< std::string /* Field Name */, std::vector< std::string > /* Vector of Values */ > Columns;   // Columns
  int                             NRows;         // Number of rows

 private:
  std::ifstream mTableFile;
};

#endif // #ifdef _TABLE_H_
