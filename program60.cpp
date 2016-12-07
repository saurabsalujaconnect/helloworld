#include<algorithm>
#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<iomanip>
#include<sstream>
#include<string>
#include<math.h>
#include<time.h>
#include<limits>
#include<stack>
#include<queue>
#include<list>
#include<map>
#include<set>

#define TS 10

using namespace std;

class Palindromes {

    struct Points {

        int start;
        int end;
        int len;

        Points() {

            this->start = -1;
            this->end = -1;
            this->len = -1;
        }

        Points( int start, int end, int len ) {

            this->start = start;
            this->end = end;
            this->len = len;
        }

        void print() {

            cout << start << " . "<< end << " . "<< len << endl;
        }
    };

    vector < vector< Points > > storage;
    vector < int > backup;

    public:

        Palindromes( int N ) : storage( N, vector< Points >() ), backup( N,0 ) {
            //
        }

        Points findLongestPalindrome( long long int a[], int N, int index, bool even ) {

            int len = 0;

            int i=index, j=index+1;

            if( even ) {
                i = index;
                j = index+1;
            } else {

                len = 1;
                i = index-1;
                j = index+1;
            }

            int found =  true;

            for( ; i>=0 && j<N ; i--, j++ ){

                if( a[i] == a[j] ){
                    len += 2;
                } else {
                    break;
                }
            }

            i++;j--;

            for( int from=i,to=j ; from <= to  ; from++,to-- ){
//                cout << from << endl;
//                cout << to << endl;

                storage[from].push_back( Points( from,to,to-from+1 ) );
            }

            return Points( i,j,len );
        }

        int findSmallestPath( int index, int N ) {

            if( index >= N ){
                return 0;
            }

            if( backup[index] != 0 ){
                return backup[index];
            }

            int min = numeric_limits <int> :: max();

            vector < Points > :: iterator it = storage[index].begin();
            for( ; it != storage[index].end() ; ++it ){

                Points point = *it;
                int val = findSmallestPath( point.end+1,N );

                if( min > val ){
                    min = val;
                }
//                point.print();
            }

            backup[index] = min+1;
            return min+1;
        }

        int givePalindrome( long long int a[], int N ) {

            for( int index=0 ; index<N ; index++ ){
                storage[index].push_back( Points( index,index,1 ) );
            }

            for( int index=0 ; index<N ; index++ ){
                if( index >= 0 && index+1 < N  && (a[index] == a[index+1]) ){
                    Points points = findLongestPalindrome( a,N,index,true );
    //                   cout << points.start << " -> "<< points.end << " -> "<< points.len << endl;
                }

                if( index-1 >= 0 && index+1 < N && (a[index-1] == a[index+1]) ){
                    Points points = findLongestPalindrome( a,N,index,false );
    //                    cout << points.start << " -> "<< points.end << " -> "<< points.len << endl;
                }
            }

/*            for( int index=0 ; index<N ; index++ ){
                vector < Points > :: iterator it = storage[index].begin();

                for( ; it != storage[index].end() ; ++it ){
                    Points point = *it;
//                    point.print();
                }

//                cout << endl;
            }
*/
            return findSmallestPath( 0,N );
        }

        int test() {

            // S : Start
            // TS : Gap

            int S=1;
            int length = 2 + rand() % TS;
            queue < int > fqe;

            for( int i=0 ; i<length ; i++ ){

                int len = 2 + rand() % ( (50*TS)/100 );
                queue < int > qe;

                /*

                50 % of TS

                */

                for( int j=0 ; j<len ; j++){

                    int val = S + (rand() % TS);

                    queue < int > storage;
                    storage.push( val );

                    while( !qe.empty() ){

                        storage.push( qe.front() );
                        qe.pop();
                    }

                    storage.push( val );
                    qe = storage;
                }

                while( !qe.empty() ){

                    fqe.push( qe.front() );
                    qe.pop();
                }

                S =+ TS + 1;
            }

            long long int a[ (2 + TS) * (( 2 + ( (50*TS)/100 )) * 2) ];
            int index = 0;

            while( !fqe.empty() ){

//                cout << fqe.front() << " " << "( " << index << " ) ,";
                a[index ++] = fqe.front();
                fqe.pop();
            }

            int vv = givePalindrome( a,index );

//            cout << "length : " << length << endl;
//            cout << "givePalindrome( a,index ) : " << vv << endl;

            if( vv == length ){

                return 1;
            }

            return 0;

//            cout << endl;
//            cout << "length : " << length << endl;
        }
};

void tester() {

    int T = 0;
    int limit = 10;

    while( T<limit ){

        Palindromes palindromes( 100 );
        if( !palindromes.test() ){
            cout << "Test Failed !!";
            break;
        }

//        system("cls");
        cout << " Running Test Cases : " << (T*100/limit) << " %" << endl;

        T++;
    }
}

int main()
{
    srand( time(0) );
    int N;
    cin >> N;

    long long int a[N];

    for( int i=0 ; i<N ; i++ ){

        cin >> a[i];
    }

    Palindromes palindromes( N );
    cout << palindromes.givePalindrome( a,N ) << endl;

    //6 9 9 6 20 13 18 16 16 18 13 20 11 20 20 11
    //64
    //7 8 8 7 17 14 19 13 17 17 13 19 14 17 18 13 18 16 19 13 13 19 16 18 13 18 13 17 18 16 16 18 17 13 14 13 13 15 18 19 19 18 15 13 13 14 13 19 11 16 16 11 19 13 15 12 12 11 12 12 11 12 12 15
//    palindromes.test();

//    tester();

    return 0;
}
