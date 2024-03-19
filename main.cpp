#include<string.h>
#include<fstream>
#include<conio.h>
#include<iomanip>
#include<iostream>
#include <algorithm>
#include <vector>
#include <shlwapi.h>

using namespace std;

//class of tickets details  - Tran Quang Dai

class Ticket{

    int roll_number;
    char ticket_type;
    char place_of_departure[50];
    char destination[50];
    int depart_day, depart_month, depart_year, depart_hour, depart_minute;
    long long ticket_price, ticket_commission;

    public:
        void get_ticket_details(int i); //get ticket details from user
        void view_ticket(int i);  //show 1 ticket
        void view_ticket(const vector<int> &match_res); //show multiple tickets
        void searchforticket(vector<Ticket> &vector_ticket, int day,int month,int year); //search by time
        void searchforticket(vector<Ticket> &vector_ticket, char place[50], int typesearch);  //search by date
        void domes_flight_in_a_period(vector<Ticket> &vector_ticket, int startDay,int startMonth,int startYear, int endDay,int endMonth,int endYear);
        void modify_ticket(vector<Ticket> &vector_ticket);
        void export_file(vector<Ticket> &vector_ticket, vector<Ticket> &vector_ticket_sold);
        void import_file(vector<Ticket> &vector_ticket, vector<Ticket> &vector_ticket_sold, Ticket &ticket);
        void FormatMoney (long long x); //printing money in format: 123.456 VND
        bool checkDateInPeriod(int day, int month, int year, int startDay, int startMonth, int startYear, int endDay, int endMonth, int endYear); //check if a date falls between a range
        friend class Ticket_sale;
};

//class of ticket sale records - Tran Quang Dai

class Ticket_sale: public Ticket{
    int sale_roll_number, ticket_roll_number;
    int ticket_sale;
    int sell_day, sell_month, sell_year;
    long long ticket_total_commission;
    public:
        void get_sale_detail(int i, int n); //get sale details from user
        void show_sale_record(int sale_roll_number);
        void export_file(vector<Ticket_sale> &vector_ticket_record);
        void import_file(vector<Ticket_sale> &vector_ticket_record, Ticket_sale &ticket_sale);
        void commission_over_a_period(vector<Ticket_sale> &vector_ticket_record, int startDay,int startMonth,int startYear, int endDay,int endMonth,int endYear);

};

//Functions declaration:
void AddTicket(vector<Ticket> &vector_ticket); //add a ticket as an object to containing vector
void DeleteTicket(vector<Ticket> &vector_ticket);
void exportfile();
void importfile();
void ModifyTicket(vector<Ticket> &vector_ticket);
void ViewTicket (vector<Ticket> &vector_ticket);
void SearchByTime(vector<Ticket> &vector_ticket);
void SearchByPlace(vector<Ticket> &vector_ticket);
void DomesticFlightInAPeriod(vector<Ticket> &vector_ticket);
void AddSaleRecord(vector<Ticket_sale> &vector_ticket_record);
void CommissionOverAPeriod(vector<Ticket_sale> &vector_ticket_record);

vector<Ticket> vector_ticket; //vector to store tickets as objects
vector<Ticket_sale> vector_ticket_record; //vector to store ticket sale records as objects
vector<Ticket> vector_ticket_sold; //vector store details of tickets sold
char ticket_data[] = "ticketdata.txt"; //file containing tickets data
char sale_record_data[] = "saledata.txt"; //file containing sales record
char ticket_sold_data[]="ticketsolddata.txt"; //file containing details of sold tickets

//main function - Tran Quang Dai
int main(){
  importfile();
  for(;;)
          {
              system("cls");
              printf("\nNumber of tickets: %zu\n\n", vector_ticket.size());
              cout << "\n\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * *";
              cout<<"\n\t\t\t\t*   1. View details of a ticket                   *";
              cout<<"\n\t\t\t\t*   2. Add a ticket                               *";
              cout<<"\n\t\t\t\t*   3. Delete a ticket                            *";
              cout<<"\n\t\t\t\t*   4. Modify a ticket                            *";
              cout<<"\n\t\t\t\t*   5. Search for a ticket                        *";
              cout<<"\n\t\t\t\t*   6. Show domestic flights in a period          *";
              cout<<"\n\t\t\t\t*   7. Calculate commission received in a period  *";
              cout<<"\n\t\t\t\t*   8. Add a sale record                          *";
              cout<<"\n\t\t\t\t*   9. Export to file                             *";
              cout<<"\n\t\t\t\t*   10.Exit                                       *";
              cout << "\n\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * *";

              int option = 0;
              cout<<"\n\t\tEnter option: "; cin>>option;
              switch(option)
              {
                    case 1:
                        system("cls");
                        ViewTicket(vector_ticket);
                        break;
                    case 2:
                        system("cls");
                        AddTicket(vector_ticket);
                        break;
                    case 3:
                        system("cls");
                        DeleteTicket(vector_ticket);
                        break;
                    case 4:
                        system("cls");
                        ModifyTicket(vector_ticket);
                        break;
                    case 5:
                        system("cls");
                        int cont_or_not;
                        do{
                        int searchopt;
                        system("cls");
                        cout<<"Enter 1 to search by time, 2 to search by location: ";
                        cin >> searchopt;
                        system("cls");
                        if (searchopt==1)
                            SearchByTime(vector_ticket);
                        else if (searchopt==2)
                            SearchByPlace(vector_ticket);
                        else cout<<"\a";

                        cout << "\n\nEnter 1 to continue searching.";
                        cout << "\nEnter 2 to return to main menu.\n";
                        cin >> cont_or_not;
                        } while(cont_or_not == 1);
                        break;
                    case 6:
                        system("cls");
                        DomesticFlightInAPeriod(vector_ticket);
                        break;
                    case 7:
                        system("cls");
                        CommissionOverAPeriod(vector_ticket_record);
                        break;
                    case 8:
                        system("cls");
                        AddSaleRecord(vector_ticket_record);
                        break;
                    case 9:
                        exportfile();
                        break;
                    case 10:
                        exit(0);
                        break;
                    default: cout<<"\a";

          }
          }

}

//functions and methods definition

void Ticket::get_ticket_details(int i) //method for getting ticket details from user - Tran Quang Dai
{
    roll_number = i;
    cout<<"\nEnter details of the ticket\n";
    cout<<"Type \"d\" for DOMESTIC and \"i\" for INTERNATIONAL ticket: "; cin>>ticket_type;

    cout<<"Enter the place of departure: ";
    cin.ignore();
    cin.getline(place_of_departure,50);

    cout << "Enter flight date (dd/mm/yyyy): ";
    char sign;
    cin >> depart_day >> sign >> depart_month >> sign >> depart_year;

    cout << "Enter boarding time (hh:mm): ";
    cin >> depart_hour >> sign >> depart_minute;

    cout<<"Enter the destination: ";
    cin.ignore();
    cin.getline(destination,50);
    fflush(stdin);

    cout<<"Enter the price of the ticket: "; cin>>ticket_price;
    double x;
    (ticket_type == 'd') ? (x =  0.05 * ticket_price) : (x =  0.07 * ticket_price + 100000);
    ticket_commission = (long long) x;
}

void AddTicket (vector<Ticket> &vector_ticket) //add ticket to the storing vector - Nguyen Anh Duy
{
    int cont_or_not;
    do
    {
        system("cls");
        Ticket ticket;
        int i = (vector_ticket.size()+1);
        ticket.get_ticket_details(i);
        vector_ticket.push_back(ticket);
        system("cls");
        cout << "\nTicket added succesfully.\n";
        ticket.view_ticket(i);
        cout << "\n\nEnter 1 to add more tickets.";
        cout << "\nEnter 2 to return to main menu.\n";
        cin >> cont_or_not;
    } while(cont_or_not == 1);
}

void DeleteTicket(vector<Ticket> &vector_ticket) //Nguyen Anh Duy
{
    int i;
    cout<<"Enter the roll number of the ticket you want to delete: "; cin>>i;
    vector_ticket.erase(vector_ticket.begin()+i-1);
    cout<<"\nTicket deleted.";
    cout<<"\n\nPress Enter to continue\n";
    fflush(stdin);
    getchar();
}

void Ticket::modify_ticket(vector<Ticket> &vector_ticket) //Tran Quang Dai
{
    Ticket ticket;
    int i;
    cout<<"Enter the roll number of the ticket you want to modify: "; cin>>i;
    ticket = vector_ticket.at(i-1);
    cout<<"\n\nModify: \n";
    int option;
    while(option != 7)
        {
            ticket.view_ticket(i);
            cout<< "\n\n\t1. Edit TYPE of ticket";
            cout<< "\n\t2. Edit PLACE OF DEPARTURE of ticket";
            cout<< "\n\t3. Edit DESTINATION of ticket";
            cout<< "\n\t4. Edit FLIGHT DATE of ticket";
            cout<< "\n\t5. Edit BOARDING TIME of ticket";
            cout<< "\n\t6. Edit PRICE of ticket";
            cout<< "\n\t7. SAVE changes.";

            cout<<"\n\t\tEnter option: "; cin>>option;
            switch(option)
            {
                case 1:
                    double y; //recalculate ticket commission
                    cout<<"Type \"d\" for domestic and \"i\" for international ticket: "; cin>> ticket.ticket_type;
                    (ticket.ticket_type == 'd') ? (y =  0.05 * ticket.ticket_price) : (y =  0.07 * ticket.ticket_price + 100000);
                    ticket.ticket_commission = (long long) y;
                    system("cls");
                    break;
                case 2:
                    cout<<"Enter new place of departure: ";
                    cin.ignore();
                    cin.getline(ticket.place_of_departure,50);
                    system("cls");
                    break;
                case 3:
                    cout<<"Enter new destination: ";
                    cin.ignore();
                    cin.getline(ticket.place_of_departure,50);
                    system("cls");
                    break;
                case 4:
                    cout << "Enter new flight date (dd/mm/yyyy): ";
                    char sign;
                    cin >> ticket.depart_day >> sign >> ticket.depart_month >> sign >> ticket.depart_year;
                    system("cls");
                    break;
                case 5:
                    cout << "Enter new boarding time (hh:mm): ";
                    cin >> ticket.depart_hour >> sign >> ticket.depart_minute;
                    system("cls");
                    break;
                case 6:
                    cout<<"Enter new price of the ticket: "; cin >> ticket.ticket_price;
                    double x; //recalculate ticket commission
                    (ticket.ticket_type == 'd') ? (x =  0.05 * ticket.ticket_price) : (x =  0.07 * ticket.ticket_price + 100000);
                    ticket.ticket_commission = (long long) x;
                    system("cls");
                    break;
               // case 7:
                   // return false;
            }
            }

    system("cls");
    cout << "\nTicket modified! New details:\n";
    ticket.view_ticket(i);
    vector_ticket.at(i-1) = ticket;
    cout<<"\n\nPress Enter to continue\n";
    fflush(stdin);
    getchar();
}

void ModifyTicket(vector<Ticket> &vector_ticket) //Nguyen Anh Duy
{
    Ticket ticket;
    ticket.modify_ticket(vector_ticket);
}


void Ticket::export_file(vector<Ticket> &vector_ticket, vector<Ticket> &vector_ticket_sold) //Tran Quang Dai
{
    FILE * fp;
    fp = fopen (ticket_data,"w");
    for(size_t i = 0;i < vector_ticket.size();i++){
            fprintf(fp, "%d,%c,%s,%s,%02d/%02d/%4d-%02d:%02d,%lld,%lld\n",
    vector_ticket[i].roll_number,
    vector_ticket[i].ticket_type,
    vector_ticket[i].place_of_departure,
    vector_ticket[i].destination,
    vector_ticket[i].depart_day,
    vector_ticket[i].depart_month,
    vector_ticket[i].depart_year,
    vector_ticket[i].depart_hour,
    vector_ticket[i].depart_minute,
    vector_ticket[i].ticket_price,
    vector_ticket[i].ticket_commission
);

                }
    fclose (fp);

    fp = fopen (ticket_sold_data,"w");
    for(size_t i = 0;i < vector_ticket_sold.size();i++){
            fprintf(fp, "%d,%c,%s,%s,%02d/%02d/%4d-%02d:%02d,%lld,%lld\n",
                        vector_ticket_sold[i].roll_number,
                        vector_ticket_sold[i].ticket_type,
                        vector_ticket_sold[i].place_of_departure,
                        vector_ticket_sold[i].destination,
                        vector_ticket_sold[i].depart_day,
                        vector_ticket_sold[i].depart_month,
                        vector_ticket_sold[i].depart_year,
                        vector_ticket_sold[i].depart_hour,
                        vector_ticket_sold[i].depart_minute,
                        vector_ticket_sold[i].ticket_price,
                        vector_ticket_sold[i].ticket_commission
                        );
                }
    fclose (fp);
}

void exportfile() //Nguyen Anh Duy
{
    Ticket ticket;
    ticket.export_file(vector_ticket, vector_ticket_sold);
    Ticket_sale ticketsale;
    ticketsale.export_file(vector_ticket_record);
    printf("Exported file successfully!");
    printf("\nPress Enter to continue.");
    fflush(stdin);
    getchar();
}


void Ticket::import_file(vector<Ticket> &vector_ticket, vector<Ticket> &vector_ticket_sold, Ticket &ticket)  //Tran Quang Dai
{
    FILE * fp;
    fp = fopen (ticket_data, "r");
    while (fscanf(fp, "%d,%c,%[^,],%[^,],%02d/%02d/%4d-%02d:%02d,%lld,%lld\n",
              &ticket.roll_number,
              &ticket.ticket_type,
              ticket.place_of_departure,
              ticket.destination,
              &ticket.depart_day,
              &ticket.depart_month,
              &ticket.depart_year,
              &ticket.depart_hour,
              &ticket.depart_minute,
              &ticket.ticket_price,
              &ticket.ticket_commission) != EOF)
{
    vector_ticket.push_back(ticket);
}


    cout << endl;
    fclose (fp);


    fp = fopen (ticket_sold_data, "r");
    while (fscanf(fp, "%d,%c,%[^,],%[^,],%02d/%02d/%4d-%02d:%02d,%lld,%lld\n",
              &ticket.roll_number,
              &ticket.ticket_type,
              ticket.place_of_departure,
              ticket.destination,
              &ticket.depart_day,
              &ticket.depart_month,
              &ticket.depart_year,
              &ticket.depart_hour,
              &ticket.depart_minute,
              &ticket.ticket_price,
              &ticket.ticket_commission) != EOF)
{
    vector_ticket_sold.push_back(ticket);
}


    cout << endl;
    fclose (fp);
}

void importfile() //Nguyen Anh Duy
{
    Ticket ticket;
    ticket.import_file(vector_ticket, vector_ticket_sold, ticket);
    Ticket_sale ticket_sale;
    ticket_sale.import_file(vector_ticket_record, ticket_sale);
}


void Ticket::view_ticket(int i) //show ticket with roll number 1 - Tran Quang Dai
{
    printf("\nTicket number %d", i);
    printf("\nType of ticket: %s", (ticket_type == 'd') ? ("Domestic") : ("International"));
    printf("\nFrom: %s", place_of_departure);
    printf("\nTo: %s", destination);
    printf("\nFlight date: %02d/%02d/%d", depart_day, depart_month, depart_year);
    printf("\nBoarding time: %02d:%02d", depart_hour, depart_minute);
    cout<<"\nPrice: "; FormatMoney(ticket_price);
    cout<<"\nCommission: "; FormatMoney(ticket_commission);
    }
void ViewTicket(vector<Ticket> &vector_ticket) // Tran Thi Thuy Linh
{
    int i;
    cout<<"\nEnter the roll number of the ticket you want to view: "; cin>>i;
    vector_ticket[i-1].view_ticket(i);
    printf("\n*******************");
    printf("\nPress Enter to continue");
    fflush(stdin);
    getchar();
}

void Ticket::view_ticket (const vector<int> &match_res) //show list of tickets with roll numbers stored in a vector - Tran Quang Dai
{
    for (size_t i = 0; i < match_res.size(); i++)
        {
            printf("\n\n*******************");
            vector_ticket[(match_res[i])].view_ticket((match_res[i])+1);
          }
}


void Ticket::FormatMoney(long long x) //print 123456 as 123.456 VND - Tran Quang Dai
{
    int fthreeDigit;
    vector <int> res;
    if (x>1000) {
            while (x !=0)
            {
                fthreeDigit = x %1000;
                res.push_back(fthreeDigit);
                x = x / 1000 ;
                }
            std::reverse(res.begin(), res.end());
            cout << res[0] << ".";
            for (size_t i = 1; i < res.size()-1; ++i)
                {
                    if (res[i] == 0)
                        cout << "000"<<".";
                    else if (res[i] < 100 && res[i] > 9)
                        cout << "0" << res[i] <<".";
                    else if (res[i] < 10 && res[i] > 0)
                        cout << "00" << res[i] <<".";
                    else
                        cout << res[i] << ".";
                        }
            if (res[res.size()-1] == 0)
                cout << "000 VND";
            else if (res[res.size()-1] < 100 && res[res.size()-1] > 9)
                cout << "0" << res[res.size()-1] <<" VND";
            else if (res[res.size()-1] < 10 && res[res.size()-1] > 0)
                cout << "00" << res[res.size()-1] <<" VND";
            else
                cout << res[res.size()-1] << " VND";
    }
    else cout << x << " VND";
}

//to check if a date is in a period - Tran Quang Dai
bool Ticket::checkDateInPeriod(int day, int month, int year, int startDay, int startMonth, int startYear, int endDay, int endMonth, int endYear)
{
    int Date = (year * 10000) + (month * 100) + day;
    int startDate = (startYear * 10000) + (startMonth * 100) + startDay;
    int endDate = (endYear * 10000) + (endMonth * 100) + endDay;

    if (Date >= startDate && Date <= endDate){
        return true;
    }
    else{
        return false;
    }
}

void Ticket::searchforticket(vector<Ticket> &vector_ticket, char place[50], int typesearch) //search by place - Tran Quang Dai
{
    int res = 0;
    vector<int> match_res;
    for(int i = 0; i < (int) vector_ticket.size(); i++){
            if ((typesearch == 1) ? ((StrStrIA(vector_ticket[i].place_of_departure, place))) : ((StrStrIA(vector_ticket[i].destination, place))))
            {
                match_res.push_back(i);
                res++;
            }
    }
    if (res == 0)
      cout << "\nNo matching ticket";
    else
      {
          printf("\n%d matching ticket%s:", res, (res==1) ? ("") : ("s"));
          view_ticket(match_res);
      }
}

void SearchByPlace(vector<Ticket> &vector_ticket) // Tran Thi Thuy Linh
{
    int typesearch;
    cout << "Enter 1 to search by place of departure, 2 to search by destination: ";
    cin>>typesearch;
    char place[50];
    system("cls");
    if (typesearch == 1)
        {cout << "Enter the place of departure to search: ";}
    else if (typesearch == 2)
        {cout << "Enter the destination to search: ";}
    fflush(stdin);
    gets(place);
    Ticket ticket;
    ticket.searchforticket(vector_ticket, place, typesearch);
}

void Ticket::searchforticket(vector<Ticket> &vector_ticket, int day,int month,int year) //search by time - //Tran Quang Dai
{
    int res = 0;
    vector<int> match_res;
    for(int i = 0; i < (int) vector_ticket.size(); i++){
        if (vector_ticket[i].depart_day == day && vector_ticket[i].depart_month == month && vector_ticket[i].depart_year == year)
        {
            match_res.push_back(i);
            res++;
        }
    }
     if (res == 0)
      cout << "\nNo matching ticket";
      else
      {
          printf("\n%d matching ticket%s:", res, (res==1) ? ("") : ("s"));
          view_ticket(match_res);
      }
}

void SearchByTime(vector<Ticket> &vector_ticket) // Tran Thi Thuy Linh
{
    cout << "Enter the flight date you want to search (dd/mm/yyyy): ";
    int day, month, year;
    char sign;
    cin >> day >> sign >> month >> sign >> year;
    Ticket ticket;
    ticket.searchforticket(vector_ticket, day, month, year);
}

void Ticket::domes_flight_in_a_period(vector<Ticket> &vector_ticket, int startDay,int startMonth,int startYear, int endDay,int endMonth,int endYear) //Tran Quang Dai
{
    int res = 0;
    vector<int> match_res;
    for(int i = 0; i < (int) vector_ticket.size(); i++){
        if (checkDateInPeriod(vector_ticket[i].depart_day, vector_ticket[i].depart_month, vector_ticket[i].depart_year, startDay, startMonth, startYear, endDay, endMonth, endYear) && (vector_ticket[i].ticket_type == 'd'))
        {
            match_res.push_back(i);
            res++;
        }
    }
     if (res == 0)
        cout << "\nThere is no domestic flight during that period.";
    else if (res == 1)
    {
        cout << "\nThere is 1 domestic flight during that period.";
        view_ticket(match_res);
    }

     else
      {
          cout << "\nThere are " << res << " domestic flights during that period.";
          view_ticket(match_res);
      }
}

void DomesticFlightInAPeriod(vector<Ticket> &vector_ticket) // Tran Thi Thuy Linh
{
    cout << "Enter the period you want to search. \n";
    cout << "\nEnter the start date(dd/mm/yyyy): ";
    int startDay, startMonth, startYear;
    char sign;
    cin >> startDay >> sign >> startMonth >> sign >> startYear;
    cout << "\nEnter the end date(dd/mm/yyyy): ";
    int endDay, endMonth, endYear;
    cin >> endDay >> sign >> endMonth >> sign >> endYear;
    Ticket ticket;
    ticket.domes_flight_in_a_period(vector_ticket, startDay, startMonth, startYear, endDay, endMonth, endYear);
    cout<<"\n\nPress Enter to continue\n";
    fflush(stdin);
    getchar();
}


void Ticket_sale::get_sale_detail(int i, int n) //Tran Quang Dai
{
    sale_roll_number = i;
    ticket_roll_number = n;
    vector_ticket_sold[i-1].view_ticket(n);
    cout<<"\nEnter the amount sold: "; cin >> ticket_sale;
    ticket_total_commission = vector_ticket_sold[sale_roll_number-1].ticket_commission * ticket_sale;
    cout << "Enter selling date (dd/mm/yyyy): ";
    char sign;
    cin >> sell_day >> sign >> sell_month >> sign >> sell_year;
}

void AddSaleRecord(vector<Ticket_sale> &vector_ticket_record) // Tran Quang Dai
{
    int cont_or_not;
    do
    {
        cout << "\nDetails of the tickets sold:";
        int n;
        cout << "\nEnter the roll number of the ticket: "; cin >> n;
        Ticket_sale salerecord;
        Ticket ticketsold;
        ticketsold = vector_ticket[n-1];
        vector_ticket_sold.push_back(ticketsold);
        int i = (vector_ticket_record.size()+1);
        salerecord.get_sale_detail(i, n);
        vector_ticket_record.push_back(salerecord);
        system("cls");
        cout << "\nSale record added successfully.\n";
        vector_ticket_record[i-1].show_sale_record(i);
        cout << "\n\nEnter 1 to add more sale records.";
        cout << "\nEnter 2 to return to main menu.\n";
        cin >> cont_or_not;
        system("cls");
    } while(cont_or_not == 1);

}

void Ticket_sale::show_sale_record(int sale_roll_number) //Tran Quang Dai
{
        int i = sale_roll_number;
        printf("\nTime: %02d/%02d/%4d", vector_ticket_record[i-1].sell_day, vector_ticket_record[i-1].sell_month, vector_ticket_record[i-1].sell_year);
        cout << "\nSale: " << vector_ticket_record[i-1].ticket_sale;
        cout << "\nDetails of tickets sold:\n";
        int n = vector_ticket_record[i-1].ticket_roll_number;
        vector_ticket_sold[i-1].view_ticket(n);
        cout << "\n\n******************************\n";
}

void Ticket_sale::export_file(vector<Ticket_sale> &vector_ticket_record) //Tran Quang Dai
{
    FILE * fp;
    fp = fopen (sale_record_data,"w");
    for(size_t i = 0;i < vector_ticket_record.size();i++){
            fprintf(fp, "%d,%d,%d,%02d/%02d/%04d,%lld\n",
                        vector_ticket_record[i].sale_roll_number,
                        vector_ticket_record[i].ticket_roll_number,
                        vector_ticket_record[i].ticket_sale,
                        vector_ticket_record[i].sell_day,
                        vector_ticket_record[i].sell_month,
                        vector_ticket_record[i].sell_year,
                        vector_ticket_record[i].ticket_total_commission
                        );
                }
    fclose (fp);
}

void Ticket_sale::import_file(vector<Ticket_sale> &vector_ticket_record, Ticket_sale &ticket_sale) //Tran Quang Dai
{
    FILE * fp;
    int i = 0;
    fp = fopen (sale_record_data, "r");
    while (fscanf(fp, "%d,%d,%d,%2d/%2d/%4d,%lld\n",
              &ticket_sale.sale_roll_number,
              &ticket_sale.ticket_roll_number,
              &ticket_sale.ticket_sale,
              &ticket_sale.sell_day,
              &ticket_sale.sell_month,
              &ticket_sale.sell_year,
              &ticket_sale.ticket_total_commission) == 7)
{
    vector_ticket_record.push_back(ticket_sale);
}


    cout << endl;
    fclose (fp);
}


void Ticket_sale::commission_over_a_period(vector<Ticket_sale> &vector_ticket_record, int startDay,int startMonth,int startYear, int endDay,int endMonth,int endYear) //Tran Quang Dai
{
    int res = 0;
    vector<int> match_res;
    for(int i = 0; i < (int) vector_ticket_record.size(); i++){
        if (checkDateInPeriod(vector_ticket_record[i].sell_day, vector_ticket_record[i].sell_month, vector_ticket_record[i].sell_year, startDay, startMonth, startYear, endDay, endMonth, endYear))
        {
            match_res.push_back(i);
            res++;
        }
    }
    long long total_commission = 0;
    for (size_t i = 0; i < match_res.size(); i++)
      {
          total_commission += vector_ticket_record[(match_res[i])].ticket_total_commission;
      }
    system("cls");
    printf("\nSale records from %02d/%02d/%04d to %02d/%02d/%04d: \n", startDay, startMonth, startYear, endDay, endMonth, endYear);
    for (size_t i = 0; i < match_res.size(); i++)
        {
		show_sale_record(match_res[i]+1);
    }
    printf("\nTotal commission received from %02d/%02d/%04d to %02d/%02d/%04d: ", startDay, startMonth, startYear, endDay, endMonth, endYear);
    FormatMoney(total_commission);



}

void CommissionOverAPeriod(vector<Ticket_sale> &vector_ticket_record) // Tran Thi Thuy Linh
{
        cout << "Enter the period you want to calculate. \n";
        cout << "\nEnter the start date(dd/mm/yyyy): ";
        int startDay, startMonth, startYear;
        char sign;
        cin >> startDay >> sign >> startMonth >> sign >> startYear;
        cout << "\nEnter the end date(dd/mm/yyyy): ";
        int endDay, endMonth, endYear;
        cin >> endDay >> sign >> endMonth >> sign >> endYear;
        Ticket_sale ticket_sale;
        ticket_sale.commission_over_a_period(vector_ticket_record, startDay, startMonth, startYear, endDay, endMonth, endYear);
        cout<<"\n\nPress Enter to continue\n";
        fflush(stdin);
        getchar();
}


