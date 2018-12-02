#ifndef HASH
#define HASH

        #include <vector>
        #include <string> 
        #include "LinkedList.h"

        template <class HashedObj>
        class HashTable
        {
          public:
            explicit HashTable( const HashedObj & notFound, int size = 101 );
            HashTable( const HashTable & rhs )
              : ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND ), theLists( rhs.theLists ) { }

            const HashedObj & find( const HashedObj & x ) const;

            void makeEmpty( );
            void insert( const HashedObj & x );
            void remove( const HashedObj & x );

            const HashTable & operator=( const HashTable & rhs );
          private:
            vector<List<HashedObj> > theLists;   // The array of Lists
            const HashedObj ITEM_NOT_FOUND;
        };

        int hash( const string& key, int tableSize );
        int hash( int key, int tableSize );

        #include "HashTable.cpp"
#endif
