#include <iostream>
#include<string>
#include"Doubly_Linked_List.h"
#include<iomanip>
#include<fstream>
#include <windows.h>
#include <mmsystem.h>
#include <thread>
#include <chrono>

using namespace std;


void clearConsole()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD count, cellCount;
    COORD homeCoords = {0, 0};

    if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        return;
    }

    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    FillConsoleOutputCharacter(hConsole, ' ', cellCount, homeCoords, &count);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, cellCount, homeCoords, &count);
    SetConsoleCursorPosition(hConsole, homeCoords);
}
void playShurah(const string& filepath)
{
    PlaySound(TEXT(filepath.c_str()), NULL, SND_FILENAME | SND_ASYNC);
}
void stopShurah()
{
    PlaySound(NULL, NULL, SND_ASYNC);
}
void print_title_shurahs();

//class Shurah
class Shurah
{
private:
    string surah_named;
    string surah_type;
    string path;
    // static size_t id=0;
public:
    Shurah():surah_named("NULL"),surah_type("NULL"),path("NULL")
    {
        //id++;
    }
    Shurah(string surah_named,string surah_type,string path)
    {
        this->surah_named=surah_named;
        this->surah_type=surah_type;
        this->path=path;
    }
    ~Shurah() {}
    void set_surah_named(string surah_named)
    {
        this->surah_named=surah_named;
    }
    string getsurah_named()const
    {
        return surah_named;
    }
    void set_surah_type(string surah_type)
    {
        this->surah_type=surah_type;
    }
    string get_surah_type()const
    {
        return surah_type;
    }
    void set_path(string path)
    {
        this->path=path;
    }
    string get_path()const
    {
        return path;
    }
    friend istream&operator>>(istream &input,Shurah &shurah)
    {
        cout<<"Enter shurah name : ";
        input>>shurah.surah_named ;
        cout<<"Enter shurah type : ";
        input>>shurah.surah_type;
        cout<<"Enter shurah path : ";
        input>>shurah.path ;
        return input;
    }
    friend ostream&operator<<(ostream &output,const Shurah &shurah)
    {
        output << left << setw(15) << shurah.surah_named << left<<setw(15) << shurah.surah_type<< left << setw(10) << shurah.path;
        return output;
    }
    Shurah &operator=(Shurah &shurah)
    {
        if(this!=&shurah)
        {
            surah_named=shurah.surah_named;
            surah_type=shurah.surah_type;
            path=shurah.path;
        }
        return *this;
    }
    bool operator==(const Shurah &shurah)const
    {

        if( surah_named==shurah.surah_named&&
                surah_type==shurah.surah_type&&
                path==shurah.path)return true;
        return false;

    }

};

//class one playlist
class One_Playlist
{
private:
    string one_playlist_name;
public:
    DLL<Shurah>shurahs;
    One_Playlist():one_playlist_name("NULL")  {}
    One_Playlist(const string &one_playlist_name)
    {
        this->one_playlist_name=one_playlist_name;
    }
    void set_playlist_name(const string &n)
    {
        one_playlist_name=n;
    }

    string get_playlist_name()const
    {
        return one_playlist_name;
    }
    void Add_shurah(const Shurah& shurah)
    {
        shurahs.Append(shurah);
    }
    Shurah get_shurah(size_t position)const
    {
        return shurahs.get_element(position);
    }

    void display_all_shurah() const
    {
        cout << "\nPlay List : " << one_playlist_name << "\n";
        cout << "----------------------------------------------------\n";
        cout << left << setw(5) << "Id" << left<<setw(15) << "Shurah Name" <<left<< setw(15) << "Shurah Type"<< left << setw(10) << "Shurah Path\n";
        cout << "----------------------------------------------------\n";
        for (size_t i = 1; i <= shurahs.size_of_list(); ++i)
        {
            cout<< i << left << setw(4)<< "." << shurahs.get_element(i) << "\n";
            cout <<"----------------------------------------------------\n";
        }
        cout<<"\n";
    }
    void remove_shurah_from_existing(size_t shurah_position)
    {
        if (shurah_position < 1 || shurah_position > shurahs.size_of_list())
        {
            throw invalid_argument("Invalid shurah position.");
        }
        shurahs.delete_from_position(shurah_position);
    }
    friend istream &operator>>(istream &input,One_Playlist&playlist)
    {

        input>>playlist.one_playlist_name;
        return input;
    }
    friend ostream &operator<<(ostream &output,const One_Playlist&playlist)
    {
        output<<"Playlist : "<<playlist.one_playlist_name;
        return output;
    }
    size_t search_by_shurah_name(string name)const
    {
        for(size_t i=1; i<=shurahs.size_of_list(); i++)
        {
            if(get_shurah(i).getsurah_named()==name)
                return i;
        }
        return 0;
    }
    void update_order_of_existing(size_t old_position,size_t new_position)
    {

        shurahs.move_element(old_position, new_position);
        cout << "Shurah order updated successfully.\n";
    }
    void print_all_shurahs() const
    {
        print_title_shurahs();
        for (size_t i = 1; i <= shurahs.size_of_list(); ++i)
        {
            cout << i << ". " << shurahs.get_element(i) << "\n";
        }
    }

};

//Manager Playlists
class Playlists_manager
{
public:
    DLL<One_Playlist>playlist_in_manager;
    Playlists_manager() {}
    void add_new_playlist(const One_Playlist& newplaylist)
    {
        playlist_in_manager.Append(newplaylist);
    }

    void display_all_playlists()const
    {
        playlist_in_manager.traverse();
    }
    void display_all_name_playlists()const
    {
        if (playlist_in_manager.size_of_list() == 0)
        {
            cout << "No playlists available.\n";
            return;
        }

        cout << "Available playlists:\n";
        for (size_t i = 1; i <= playlist_in_manager.size_of_list(); i++)
        {
            cout << i << ". " ;
            cout<< playlist_in_manager.get_element(i).get_playlist_name();
            cout<< "\n";
        }
    }


    size_t search_by_playlist_name(const string& name)const
    {
        for(size_t i=1; i<=playlist_in_manager.size_of_list(); i++)
        {
            if(playlist_in_manager.get_element(i).get_playlist_name()==name)return i;
        }
        return 0;
    }
    friend ostream &operator<<(ostream&output,Playlists_manager&mang)
    {
        output<<mang.playlist_in_manager;
        return output;
    }
    //save file
    void savefile()
    {
        ofstream output;
        output.open("playlist_manager.txt");
        output<<playlist_in_manager.size_of_list()<<"\n";
        for(size_t i=1; i<=playlist_in_manager.size_of_list(); i++)
        {
            output<<"playlist "<<playlist_in_manager.get_element(i).get_playlist_name()<<"\n";
            output<<playlist_in_manager.get_element(i).shurahs.size_of_list()<<"\n";
            for(size_t j=1; j<=playlist_in_manager.get_element(i).shurahs.size_of_list(); j++)
            {
                output<<playlist_in_manager.get_element(i).shurahs.get_element(j).getsurah_named()<<" ";
                output<<playlist_in_manager.get_element(i).shurahs.get_element(j).get_surah_type()<<" ";
                output<<playlist_in_manager.get_element(i).shurahs.get_element(j).get_path();
                output<<"\n";

            }

        }

        output.close();

    }
};

//function to load data from file
Playlists_manager loadfile()
{
    Playlists_manager manager;
    One_Playlist new_playlist;
    Shurah new_shurah;
    ifstream input("playlist_manager.txt");
    if (!input.is_open())
    {
        cout << "Error opening file.\n";
        return manager;
    }

    size_t playlist_count;
    input >> playlist_count;
    for (size_t i = 0; i < playlist_count; ++i)
    {
        string playlist_name;
        input.ignore();
        if (getline(input, playlist_name))
        {
            size_t pos = playlist_name.find("playlist ");
            if (pos != string::npos)
            {
                playlist_name = playlist_name.substr(pos + 9);
            }
            else
            {
                cerr << "Error: Playlist format is incorrect.\n";
                continue;
            }
        }

        size_t shurah_count;
        input >> shurah_count;
        new_playlist.set_playlist_name(playlist_name);
        input.ignore();
        for (size_t j = 0; j < shurah_count; ++j)
        {
            string line, shurah_name, shurah_type, path;
            if (getline(input, line))
            {
                size_t pos = line.find(" ");
                if (pos == string::npos)
                {
                    cerr << "Error: Invalid Shurah format.\n";
                    continue;
                }
                shurah_name = line.substr(0, pos);
                line = line.substr(pos + 1);

                pos = line.find(" ");
                if (pos == string::npos)
                {
                    cerr << "Error: Invalid Shurah format.\n";
                    continue;
                }
                shurah_type = line.substr(0, pos);
                line = line.substr(pos + 1);
                path = line;
            }

            new_shurah.set_surah_named(shurah_name);
            new_shurah.set_surah_type(shurah_type);
            new_shurah.set_path(path);

            new_playlist.shurahs.Append(new_shurah);
        }

        manager.playlist_in_manager.Append(new_playlist);
        cout << "Playlist added: " << new_playlist.get_playlist_name() << endl;

        manager.playlist_in_manager.get_element(i + 1).shurahs.traverse();
    }
    cout << "Data loaded successfully from playlist_manager.txt.\n";

    input.close();
    return manager;
}

//function to play playlists
void playPlaylistShurah(Playlists_manager& manager, size_t playlist_index)
{
    DLL<string> playlist_paths;
    size_t playlist_size = manager.playlist_in_manager.get_element(playlist_index).shurahs.size_of_list();

    for (size_t i = 1; i <= playlist_size; ++i)
    {
        playlist_paths.Append(
            manager.playlist_in_manager.get_element(playlist_index).shurahs.get_element(i).get_path()
        );
    }

    size_t currentIndex = 1;
    bool isPaused = false;
    cout << "Playing first shurah: " << playlist_paths.get_element(currentIndex) << endl;
    playShurah(playlist_paths.get_element(currentIndex));

    while (true)
    {
        if (GetAsyncKeyState(VK_LEFT))  // <-
        {
            if (currentIndex > 1)
            {
                stopShurah();
                currentIndex--;
                playShurah(playlist_paths.get_element(currentIndex));
                cout << "Playing previous shurah: " << playlist_paths.get_element(currentIndex) << endl;
            }
            this_thread::sleep_for(chrono::milliseconds(300));
        }
        if (GetAsyncKeyState(VK_RIGHT))   // ->
        {
            if (currentIndex < playlist_size)
            {
                stopShurah();
                currentIndex++;
                playShurah(playlist_paths.get_element(currentIndex));
                cout << "Playing next shurah: " << playlist_paths.get_element(currentIndex) << endl;
            }
            this_thread::sleep_for(chrono::milliseconds(300));
        }
        if (GetAsyncKeyState(VK_UP))   // ^
        {
            if (!isPaused)
            {
                stopShurah();
                isPaused = true;
                cout << "Shurah paused." << endl;
            }
            this_thread::sleep_for(chrono::milliseconds(300));
        }
        if (GetAsyncKeyState(VK_DOWN))   // v
        {
            if (isPaused)
            {
                playShurah(playlist_paths.get_element(currentIndex));
                isPaused = false;
                cout << "Resumed playing: " << playlist_paths.get_element(currentIndex) << endl;
            }
            this_thread::sleep_for(chrono::milliseconds(300));
        }
        if (GetAsyncKeyState('Q'))   //exit
        {
            stopShurah();
            cout << "Exiting playback...\n";
            break;
        }
    }
}


void menu()
{
    cout<<"\t\t\t\t\t\t+============================================================+\n";
    cout<<"\t\t\t\t\t\t|              Quraan Playlist Manager Menu                  |\n";
    cout<<"\t\t\t\t\t\t+============================================================+\n";
    cout<<"\t\t\t\t\t\t| 1. Add a new playlist                                      |\n";
    cout<<"\t\t\t\t\t\t| 2. Add shurah to an exisiting                              |\n";
    cout<<"\t\t\t\t\t\t| 3. Remove Shurah from an existing playlist                 |\n";
    cout<<"\t\t\t\t\t\t| 4. Update the order of existing playlist                   |\n";
    cout<<"\t\t\t\t\t\t| 5. Display All Current Playlists                           |\n";
    cout<<"\t\t\t\t\t\t| 6. Display all Playlists Shurah                            |\n";
    cout<<"\t\t\t\t\t\t| 7. Display Shurah in a specific playlist                   |\n";
    cout<<"\t\t\t\t\t\t| 8. Play Shurah from specific playlist                      |\n";
    cout<<"\t\t\t\t\t\t|    Use left arrow (<-) to play the previous shurah         |\n";
    cout<<"\t\t\t\t\t\t|    Use right arrow (->) to play the next shurah            |\n";
    cout<<"\t\t\t\t\t\t|    Use up arrow (^) to pause the current shurah            |\n";
    cout<<"\t\t\t\t\t\t|    Use down arrow (v) to resume the current shurah         |\n";
    cout<<"\t\t\t\t\t\t| Press q to exit current playlist & return back to menu     |\n";
    cout<<"\t\t\t\t\t\t| 9. Save an existing playlist to a file                     |\n";
    cout<<"\t\t\t\t\t\t| 10. Load an existing playlist from a file                  |\n";
    cout<<"\t\t\t\t\t\t| 11. Remove an existing playlist                            |\n";
    cout<<"\t\t\t\t\t\t| 12. Exit                                                   |\n";
    cout<<"\t\t\t\t\t\t+============================================================+\n";

}
void print_title_shurahs()
{
    cout<<"\t----------------------------------------------------\n";
    cout<<"\t"<<left<<setw(5)<<"Id"<<left<<setw(15)<<"Shurah Name"<<left<<setw(10)<<"Shurah Type"<<" Shurah Path\n";
    cout<<"\t----------------------------------------------------\n";
}

int main()
{
    cout<<"\t\t\t\t\t\t\tQuraan Playlist Manager Simulation System\n";
    cout<<"\t\t\t\t\t\t\t               Developed By\n";
    cout<<"\t\t\t\t\t\t\t           Mohamed Yasser Raya\n\n";

    bool flag=true;
    Playlists_manager manager;
    while(flag)
    {
        int choice;
        bool check;
        menu();
        do
        {
            check=1;
            cout<<"\t\t\t\t\t\tEnter Choice :";
            cin>>choice;
            if(choice>12||choice<1)
            {
                check=0;
                cout<<"Wrong ! Please Enter Correct Choice...\n";
            }
            else if(manager.playlist_in_manager.size_of_list()==0&& !(choice==1 || choice==12 ||choice==10))
            {
                check=0;
                cout<<"No Playlists available !\nPlease Add a playlist first.\n";

            }
        }
        while(!check);
        //Playlists are a container contain every play list
        if(choice!=12)clearConsole();

        switch(choice)
        {
        //Add a new playlist
        case 1:
        {
            One_Playlist new_playlist;
            cout<<"Enter playlist name : ";
            cin >> new_playlist;
            manager.add_new_playlist(new_playlist);
            // print_when_add_playlist();

            cout << "Playlist \"" << new_playlist.get_playlist_name() << "\" added successfully.\n";
            break;
        }
        //Add shurah to an exisiting
        case 2:
        {
            if (manager.playlist_in_manager.size_of_list() == 0)
            {
                cout << "No playlists available. Please add a playlist first.\n";
                break;
            }
            clearConsole();

            manager.display_all_name_playlists();

            size_t playlist_choice;
            cout << "Select the playlist number to add a Shurah: ";
            cin >> playlist_choice;

            if (playlist_choice < 1 || playlist_choice > manager.playlist_in_manager.size_of_list())
            {
                cout << "Invalid choice.\n";
                break;
            }

            One_Playlist& selected_playlist = manager.playlist_in_manager.get_element(playlist_choice);

            bool if_need;
            do
            {
                if_need = 0;
                Shurah new_shurah;
                cin >> new_shurah;

                selected_playlist.shurahs.Append(new_shurah); // التعديل المباشر على الكائن
                cout << "Shurah added to playlist successfully.\n";

                cout << "Do you need to add another shurah to the current playlist? (1: Yes, 0: No): ";
                cin >> if_need;
            }
            while (if_need);

            break;
        }

        //Remove Shurah from an existing playlist
        case 3:
        {
            string name;
            cout<<"Enter play list name : ";
            cin>>name;
            size_t playlist_position=manager.search_by_playlist_name(name);
            if(playlist_position==0)
            {
                cout<<"No play list by this name .\n";
                break;
            }
            cout<<"Enter shurah name : ";
            cin>>name;
            size_t shurah_position=manager.playlist_in_manager.get_element(playlist_position).search_by_shurah_name(name);
            if (shurah_position == 0)
            {
                cout << "No shurah by this name.\n";
                break;
            }
            string shurah_name = manager.playlist_in_manager.get_element(playlist_position).get_shurah(shurah_position).getsurah_named();
            manager.playlist_in_manager.get_element(playlist_position).remove_shurah_from_existing(shurah_position);
            cout << "Shurah '" << shurah_name << "' removed from play list.\n";



            break;
        }
        //Update the order of existing playlist
        case 4:
        {
            string name;
            cout << "Enter the name of the playlist: ";
            cin >>name;
            size_t playlist_position = manager.search_by_playlist_name(name);

            if (playlist_position == 0)
            {
                cout << "No play list by this name .\n";
                break;
            }

            cout << "Enter the name of the Shurah to move: ";
            cin >>name;
            size_t old_position =manager.playlist_in_manager.get_element(playlist_position).search_by_shurah_name(name);
            if (old_position == 0)
            {
                cout << "No shurah by this name.\n";
                break;
            }
            size_t new_position;
            cout << "Enter the new position: ";
            cin >> new_position;

            manager.playlist_in_manager.get_element(playlist_position).shurahs.move_element(old_position,new_position);
            cout<<"Shurah' "<<name<<" ' moved to position "<<new_position<<endl;

            break;
        }

        //Display All Current Playlists
        case 5:
        {
            manager.display_all_playlists();

            break;
        }
        //Display all Playlists Shurah
        case 6:
        {
            if (manager.playlist_in_manager.size_of_list() == 0)
            {
                cout << "No playlists available.\n";
                break;
            }

            for (size_t i = 1; i <= manager.playlist_in_manager.size_of_list(); ++i)
            {

                if (manager.playlist_in_manager.get_element(i).shurahs.size_of_list() == 0)
                {
                    cout << "No shurahs in "<<manager.playlist_in_manager.get_element(i)<<" .\n";
                }
                else
                {
                    manager.playlist_in_manager.get_element(i).display_all_shurah();
                }
            }

            break;
        }

        //Display Shurah in a specific playlist
        case 7:
        {
            if (manager.playlist_in_manager.size_of_list() == 0)
            {
                cout << "No playlists available.\n";
                break;
            }
             manager.display_all_name_playlists();
              size_t playlist_index;
            cout << "Enter playlist number to display Shurahs: ";
            cin >> playlist_index;
             if (manager.playlist_in_manager.get_element(playlist_index).shurahs.size_of_list() == 0)
                {
                    cout << "No shurahs in this playlist.\n";
                    break;
                }


            if (playlist_index < 1 || playlist_index > manager.playlist_in_manager.size_of_list())
            {
                cout << "Invalid playlist number.\n";
                break;
            }

            manager.playlist_in_manager.get_element(playlist_index).display_all_shurah();


            break;
        }
        //Play Shurah from specific playlist
        case 8:
        {
            size_t playlist_index;
            manager.display_all_name_playlists();
            cout << "Enter playlist number to play shurahs: ";
            cin >> playlist_index;
            if (playlist_index < 1 || playlist_index > manager.playlist_in_manager.size_of_list())
            {
                cout << "Invalid playlist number.\n";
                break;
            }
            if(manager.playlist_in_manager.get_element(playlist_index).shurahs.size_of_list()==0){
                cout<<"No Shurahs in "<<manager.playlist_in_manager.get_element(playlist_index)<<"\n";
                break;
            }
            playPlaylistShurah(manager, playlist_index);
            break;
        }

        //Save an existing playlist to a file
        case 9:
        {
            manager.savefile();
            cout<<"All play list saved...\n";
            break;
        }

        //Load an existing playlist from a file
        case 10:
        {
            Playlists_manager load_manager = loadfile();
            cout << "Loading data from file...\n";

            if (load_manager.playlist_in_manager.size_of_list() == 0)
            {
                cout << "No playlists found in the loaded file.\n";
            }
            else
            {
                cout << "Loaded playlists:\n";
                for (size_t i = 1; i <= load_manager.playlist_in_manager.size_of_list(); ++i)
                {
                    cout << "Playlist name: " << load_manager.playlist_in_manager.get_element(i).get_playlist_name() << endl;
                    load_manager.playlist_in_manager.get_element(i).display_all_shurah();
                }
            }

            for (size_t i = 1; i <= load_manager.playlist_in_manager.size_of_list(); ++i)
            {
                string playlist_name = load_manager.playlist_in_manager.get_element(i).get_playlist_name();
                if(manager.playlist_in_manager.size_of_list()==0)
                {
                    manager.playlist_in_manager.insert_at_begin(load_manager.playlist_in_manager.get_element(i));

                }
                else
                {

                    manager.playlist_in_manager.Append(load_manager.playlist_in_manager.get_element(i));
                    cout << "Playlist " << playlist_name << " added to manager.\n";
                }
            }

            cout << "Data loaded successfully...\n";

            break;
        }



        // Remove an existing playlist
        case 11:
        {
            string name;
            cout<<"Enter play list name : ";
            cin>>name;
            size_t playlist_position=manager.search_by_playlist_name(name);
            if(playlist_position==0)
            {
                cout<<"No play list by this name .\n";
                break;
            }
            cout<<"' "<<manager.playlist_in_manager.get_element(playlist_position)<<" ' is deleted\n";

            manager.playlist_in_manager.delete_from_position(playlist_position);

            break;
        }
        //Exit
        case 12:
        {
            flag=false;
            cout<<"\tExiting...\n";
        }


        }

    }
    cout<<"\t\t\t\t\t\t\t               Developed By\n";
    cout<<"\t\t\t\t\t\t\t           Mohamed Yasser Raya\n";

    return 0;
}
