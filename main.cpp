/* 
 * Ferienwohnung Management
 * File:   main.cpp
 * 
 * Author: Dominic Reich <dominic@tmsn.at>
 * Created on 20. Februar 2016, 16:11
 * Last modified: Freitag, 04.03.2016 23:39
 * 
 * The MIT License (MIT) {{{
 * 
 * Copyright (c) 2015 Dominic Reich
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. }}}
 * 
 */

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <limits>
#include <string>
#include "version.h"

using namespace std;

/*
 * Einige Definitionen
 */
#define MAX_LIST 5
#define LICENSE_FILE "LICENSE"

//#ifndef _WIN32
  #define HEADER    "\033[1;34mDie Schwarze Liste\033[0m\n"
  #define LINES     "\033[1;34m-------------------------------------------------------------------------------\033[0m"
  #define INFOLINE  "\033[1;34mSchwarze Liste    (C) 2016 Dominic Reich\033[0m\n"
//#else
//  #define HEADER    "Die Schwarze Liste\n"
//  #define LINES     "-------------------------------------------------------------------------------"
//  #define INFOLINE  "Schwarze Liste    (C) 2016 Dominic Reich\n"
//#endif

/*
 * Function prototypes
 */
void ClearScreen();
char GetChoice( unsigned int &x );
void NewEntry( unsigned int &x, const char *Filename, const char *Counter );
void ListGuests( unsigned int &x, const char *Filename );
void PrintInfo();
void PressKeyToContinue();
void SearchGuests( unsigned int &x, const char *Filename );
void PrintSingleGuest( unsigned int &x, unsigned int Id, string Name, string Strasse, string Plz, string Ort, string Telefon, string Email, string Kommentar, bool Active );
//inline bool FileExists( const string& name );
void SetTitle( string sTitle );
string SetBoldText( string Text );
void ToggleEntry( const char *Filename, const char *Counter );

/*
 * Main
 */
int main( int argc, char** argv ) {
    
    char cAuswahl;
    const char * cFilename = "daten.txt";
    const char * cCounter  = "counter.txt";
    
    unsigned int iGesamt = 0;
    unsigned int * pGesamt;
    pGesamt = &iGesamt;
    
    ClearScreen();
    SetTitle( "Ferienwohnung Reich : Blacklist" );
    
    do{
        ifstream Counter( cCounter, ios::in );
        if( !Counter.is_open() ){
            cout << "Konnte Datei " << cCounter << " nicht oeffnen!" << endl;
            exit(1);
        }
        Counter >> *pGesamt;
        Counter.close();
        
        cAuswahl = GetChoice( *pGesamt );
        
        switch( cAuswahl ) {
            case 'n':
            case 'N': {
                //ClearScreen();
                cout << "\nBitte geben Sie die Daten des Gastes ein.\n" << endl;
                NewEntry( *pGesamt, cFilename, cCounter );
                ClearScreen();
                break;
            }
            case 's':
            case 'S': {
                //ClearScreen();
                SearchGuests( *pGesamt, cFilename );
                ClearScreen();
                break;
            }
            case 'l':
            case 'L': {
                ClearScreen();
                ListGuests( *pGesamt, cFilename );
                ClearScreen();
                break;
            }
            case 'a':
            case 'A': {
                ToggleEntry( cFilename, cCounter );
                ClearScreen();
                break;
            }
            case 'i':
            case 'I': {
                ClearScreen();
                PrintInfo();
                ClearScreen();
                break;
            }
            case 'q':
            case 'Q': {
                /* This is exit */
                break;
            }
            default: {
                ClearScreen();
            }
        }
    } while ( cAuswahl != 'q' && cAuswahl != 'Q' );

    return 0;
}

/*
 * ClearScreen
 */
void ClearScreen() {
#ifndef _WIN32
    cout << "\033[2J\033[1;1H";
#else
    system( "cls" );
#endif
}

/*
 * GetChoice
 */
char GetChoice( unsigned int &x ) {
    int bis;
    char Choice;
    
    unsigned int * px = &x;
    
    if( *px < MAX_LIST ) {
        bis = *px;
    } else {
        bis = MAX_LIST;
    }
    
    cout << HEADER;
    cout << LINES << endl;
    cout << "  [ n ] Neuen Gast hinzufuegen\n";
    cout << "  [ s ] Nach Gast suchen\n";
    cout << "  [ l ] Die letzten " << bis << " Gaeste zeigen\n";
    cout << "  [ a ] Einen Datensatz (in)aktiv setzen\n";
    cout << "  [ i ] Info (About)\n";
    cout << "  [ q ] Programm beenden\n" << endl;
    cout << "Auswahl: ";
    cin >> Choice;
    
    return Choice;
}

/*
 * NewEntry
 */
void NewEntry( unsigned int &x, const char *Filename, const char *Counter ) {
    int pos = 0;
    cin.ignore();
    
    ofstream DataFile( Filename, ios::out | ios::app );
    if( !DataFile.is_open() ) {
        cout << "Konnte die Datei " << Filename << " nicht oeffnen." << endl;
        exit(1);
    }
    string Name, Strasse, Plz, Ort, Telefon, Email, Kommentar;
    cout << "Vor- und Nachname:    ";
    getline( cin, Name );
    cout << "Straße inkl. Hausnr.: ";
    getline( cin, Strasse );
    cout << "PLZ:                  ";
    getline( cin, Plz );
    cout << "Ort:                  ";
    getline( cin, Ort );
    cout << "Telefon:              ";
    getline( cin, Telefon );
    cout << "Email:                ";
    getline( cin, Email );
    cout << "Kommentar:            ";
    getline( cin, Kommentar );
    
    if( Telefon.empty() ) Telefon = "-";
    if( Email.empty() ) Email = "-";
    if( Kommentar.empty() ) Kommentar = "-";
    
    while( ( pos = Name.find(' ')) != string::npos ) Name[pos] = '*';
    while( ( pos = Strasse.find(' ')) != string::npos ) Strasse[pos] = '*';
    while( ( pos = Ort.find(' ')) != string::npos ) Ort[pos] = '*';
    while( ( pos = Telefon.find(' ')) != string::npos ) Telefon[pos] = '*';
    while( ( pos = Email.find(' ')) != string::npos ) Email[pos] = '*';
    while( ( pos = Kommentar.find(' ')) != string::npos ) Kommentar[pos] = '*';

    unsigned int * px = &x;
    ++*px;
    DataFile << *px << "\t" << Name << "\t" << Strasse << "\t" << Plz << "\t";
    DataFile << Ort << "\t" << Telefon << "\t" << Email << "\t" << Kommentar;
    DataFile << "\t1" << endl;
    DataFile.close();
    
    ofstream CounterFile( Counter, ios::out );
    if( !CounterFile.is_open() ) {
        cout << "Konnte die Datei " << Counter << " nicht oeffnen." << endl;
        exit(1);
    }
    
    CounterFile << *px;
    CounterFile.close();
}

/*
 * ListGuests
 */
void ListGuests( unsigned int &x, const char *Filename ) {
    unsigned int * px = &x;
    int bis;
    
    if( *px < MAX_LIST ) {
        bis = 0;
    } else {
        bis = *px - MAX_LIST;
    }
    
    ifstream DataFile( Filename, ios::in );
    if( !DataFile.is_open() ) {
        cout << "Konnte die Datei " << Filename << " nicht oeffnen." << endl;
        exit(1);
    }
    
    unsigned int Id;
    string Name, Strasse, Plz, Ort, Telefon, Email, Kommentar;
    bool Active;
    
    cout << "Es werden die letzten " << *px - bis << " Eintraege angezeigt.\n" << endl;
    cout << LINES << endl;
    
    DataFile.seekg( ios::beg );
    for( int i = 0; i < bis; i++ ) {
        DataFile.ignore( numeric_limits<streamsize>::max(), '\n' );
    }
    
    while( DataFile >> Id >> Name >> Strasse >> Plz >> Ort >> Telefon >> Email >> Kommentar >> Active ) {
        PrintSingleGuest( *px, Id, Name, Strasse, Plz, Ort, Telefon, Email, Kommentar, Active );
    }
    
    DataFile.close();
    PressKeyToContinue();
}

/*
 * PrintInfo
 */
void PrintInfo() {
    cout << INFOLINE << LINES << endl;
#ifndef _WIN32
    cout << "\033[1;32m";
#endif
    cout << "\n Dominic Reich       Kontakt: dominic@mm.st\n";
    cout << " Seite 37                     http://tmsn.at\n 6433 Oetz\n";
    cout << " AUSTRIA             Version: " << Version::FULLVERSION_STRING << Version::STATUS_SHORT;
    cout << " (" << Version::STATUS << ")\n\n";
    cout << " https://github.com/freefallcid/Fewo-Blacklist/\n\n";
#ifndef _WIN32
    cout << "\033[0m";
#endif
    
    cout << "Dieses Programm ist lizenziert unter der MIT Lizenz.\n";
    
    //PressKeyToContinue();
    string line;
    
    ifstream LicenseFile( LICENSE_FILE );
    if( !LicenseFile.is_open() ) {
        cout << endl;
        cout << " Die MIT Lizenz kann unter http://opensource.org/licenses/MIT \n nachgelesen werden.\n\n";
        cin.get();
    } else {
        PressKeyToContinue();
        ClearScreen();
        cout << endl;
        while( getline( LicenseFile, line )) {
            cout << line << endl;
        }
    }
    
    LicenseFile.close();
    
    cout << "Weiter mit <ENTER>";
    cin.get();
    //PressKeyToContinue();
}

/*
 * PressKeyToContinue
 */
void PressKeyToContinue() {
    cout << "\nWeiter mit <ENTER>";
    cin.ignore(1);
    cin.get();
}

/*
 * SearchGuests
 */
void SearchGuests( unsigned int &x, const char *Filename ) {
    unsigned int * px = &x;
    
    ifstream DataFile( Filename, ios::in );
    if( !DataFile.is_open() ) {
        cout << "Konnte die Datei " << Filename << "nicht oeffnen." << endl;
        exit(1);
    }
    
    unsigned int Id;
    string Name, Strasse, Plz, Ort, Telefon, Email, Kommentar;
    bool Active;
    int pos = 0;
    
    string s = "";
    string f = "";
    
    cin.ignore();
    //DataFile.seekg(0, DataFile.beg);
    
    cout << "\nSuchbegriff: ";
    getline( cin, s );
    while( ( pos = s.find(' ')) != string::npos ) s[pos] = '*';
    
    ClearScreen();
    
//#ifndef _WIN32
    cout << "\033[1;34mSuchergebnisse fuer '\033[1;32m" << s << "\033[1;34m':\033[0m\n" << endl;
//#else
//    cout << "Suchergebnisse fuer '" << s << "':\n" << endl;
//#endif
    cout << LINES << endl;
    
    while( DataFile >> Id >> Name >> Strasse >> Plz >> Ort >> Telefon >> Email >> Kommentar >> Active ) {
        f = Name + " " + Strasse + " " + Plz + " " + Ort + " " + Telefon + " " + Email + " " + Kommentar;
        size_t found = f.find( s );
        if( found != string::npos ) {
            PrintSingleGuest( *px, Id, Name, Strasse, Plz, Ort, Telefon, Email, Kommentar, Active );
        }
    }
    
    cout << "\nWeiter mit <ENTER>";
    cin.get();
    //PressKeyToContinue();
    
    ClearScreen();
    DataFile.close();
    //PressKeyToContinue();
}

/*
 * PrintSingleGuest
 */
void PrintSingleGuest( unsigned int &x, unsigned int Id, string Name, string Strasse, string Plz, string Ort, string Telefon, string Email, string Kommentar, bool Active ) {
    unsigned int * px = &x;
    int pos = 0;
    string sAktiv = "";
    
    if( Active == true ) {
        sAktiv = "AKTIV";
    } else {
        sAktiv = "INAKTIV";
    }
    
    while( ( pos = Name.find('*')) != string::npos ) Name[pos] = ' ';
    while( ( pos = Strasse.find('*')) != string::npos ) Strasse[pos] = ' ';
    while( ( pos = Ort.find('*')) != string::npos ) Ort[pos] = ' ';
    while( ( pos = Telefon.find('*')) != string::npos ) Telefon[pos] = ' ';
    while( ( pos = Email.find('*')) != string::npos ) Email[pos] = ' ';
    while( ( pos = Kommentar.find('*')) != string::npos ) Kommentar[pos] = ' ';
   
    cout << SetBoldText( Name ) << ", " << Strasse << ", " << Plz << " " << Ort << "\n";
    cout << "Email: " << SetBoldText( Email ) << "\tTelefon: " << Telefon;
    cout << "\nKommentar: " << Kommentar;
    cout << "\nDatensatz: " << SetBoldText( to_string( Id )) << "/";
    cout << *px << "\t(" << sAktiv << ")" << endl;
    //cout << "Datensatz: " << Id << "/" << *px << " (Aktiv: " << Active << ")" << endl;
    cout << LINES << endl;
}

/*
 * FileExists
 */
//inline bool FileExists( const string &name ) {
//    struct stat buffer;
//    return ( stat ( name.c_str(), &buffer ) == 0 );
//}

/*
 * SetTitle
 */
void SetTitle( string sTitle ) {
#ifndef _WIN32
    char esc_start[] = { 0x1b, ']', '0', ';', 0 };
    char esc_end[] = { 0x07, 0 };
    cout << esc_start << sTitle.c_str() << esc_end;
#else
//    system( sTitle.c_str() );
#endif
}

/*
 * SetBoldText
 */
string SetBoldText( string Text ) {
#ifndef _WIN32
    return "\033[1;37m" + Text + "\033[0m";
#else
    return Text;
#endif
}

/*
 * ToggleEntry
 */
void ToggleEntry( const char *Filename, const char *Counter ) {
//    int pos = 0;
//    cin.ignore();
//    
//    ofstream DataFile( Filename, ios::out | ios::app );
//    if( !DataFile.is_open() ) {
//        cout << "Konnte die Datei " << Filename << " nicht oeffnen." << endl;
//        exit(1);
//    }
//    string Name, Strasse, Plz, Ort, Telefon, Email, Kommentar;
//    
//    DataFile.close();
    cout << "Sorry, diese Funktion ist noch in Arbeit." << endl;
    PressKeyToContinue();
}

/* vim: set ts=2 sw=2 tw=0 et :*/

