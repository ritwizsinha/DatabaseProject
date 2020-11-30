// Script for generating all  the data
// The data must be added taking care of the foreign key constraint

#include <bits/stdc++.h>
#include <fstream>
using namespace std;
#define mx 60
#define noAdd 60
#define transport_mx 100
#define ships 100
#define rndi (int)1e9+7;
map<int,int> mpx;
vector<string> firstNames = { "Adam", "Alex", "Aaron", "Ben", "Carl", "Dan", "David", "Edward", "Fred", "Frank", "George", "Hal", "Hank", "Ike", "John", "Jack", "Joe", "Larry", "Monte", "Matthew", "Mark", "Nathan", "Otto", "Paul", "Peter", "Roger", "Roger", "Steve", "Thomas", "Tim", "Ty", "Victor", "Walter"};
vector<string> lastNames = { "Anderson", "Ashwoon", "Aikin", "Bateman", "Bongard", "Bowers", "Boyd", "Cannon", "Cast", "Deitz", "Dewalt", "Ebner", "Frick", "Hancock", "Haworth", "Hesch", "Hoffman", "Kassing", "Knutson", "Lawless", "Lawicki", "Mccord", "McCormack", "Miller", "Myers", "Nugent", "Ortiz", "Orwig", "Ory", "Paiser", "Pak", "Pettigrew", "Quinn", "Quizoz", "Ramachandran", "Resnick", "Sagar", "Schickowski", "Schiebel", "Sellon", "Severson", "Shaffer", "Solberg", "Soloman", "Sonderling", "Soukup", "Soulis", "Stahl", "Sweeney", "Tandy", "Trebil", "Trusela", "Trussel", "Turco", "Uddin", "Uflan", "Ulrich", "Upson", "Vader", "Vail", "Valente", "Van Zandt", "Vanderpoel", "Ventotla", "Vogal", "Wagle", "Wagner", "Wakefield", "Weinstein", "Weiss", "Woo", "Yang", "Yates", "Yocum", "Zeaser", "Zeller", "Ziegler", "Bauer", "Baxster", "Casal", "Cataldi", "Caswell", "Celedon", "Chambers", "Chapman", "Christensen", "Darnell", "Davidson", "Davis", "DeLorenzo", "Dinkins", "Doran", "Dugelman", "Dugan", "Duffman", "Eastman", "Ferro", "Ferry", "Fletcher", "Fietzer", "Hylan", "Hydinger", "Illingsworth", "Ingram", "Irwin", "Jagtap", "Jenson", "Johnson", "Johnsen", "Jones", "Jurgenson", "Kalleg", "Kaskel", "Keller", "Leisinger", "LePage", "Lewis", "Linde", "Lulloff", "Maki", "Martin", "McGinnis", "Mills", "Moody", "Moore", "Napier", "Nelson", "Norquist", "Nuttle", "Olson", "Ostrander", "Reamer", "Reardon", "Reyes", "Rice", "Ripka", "Roberts", "Rogers", "Root", "Sandstrom", "Sawyer", "Schlicht", "Schmitt", "Schwager", "Schutz", "Schuster", "Tapia", "Thompson", "Tiernan", "Tisler" };
string rs(int size) {
    string s;
    s.resize(size);
    for(int i=0;i<size;i++) s[i] = ('a' + rand()%26);
    return s;
}
string rp() {
    string s;
    s.resize(10);
    for(int i=0;i<10;i++) s[i] = (char)('0' + (rand()%10));
    return s;
}

string rd() {
    string s;
    s.reserve(10);
    s+= to_string(2000 + rand()%23);
    s+="-";
    s+=to_string(11 + rand()%2);
    s+="-";
    s+=to_string(10 + rand()%20);
    return s;
}
struct Transport {
    int _id;
    string type;
    int cost_per_km;
    int identification_code;
    int model_no;
};
struct deliveryStatus {
    int _id;
    string status;
    string details;
};
struct packageType {
    int _id;
    string type;
    string details;
};
struct user {
    int _id;
    string firstName;
    string lastName;
    int address_id;
    int debts;
    string phone;
    string email;
    string registered_date;
    string creditcard;
    int total_spent;
    int registered;
};
struct address {
    int _id;
    string address;
    string locality;
    string city;
    string state;
    string pincode;
    string country;
};
struct receiver {
    int _id;
    int address_id;
    string name;
    string phone;
    int registered;
};
struct transaction {
    int _id;
    int customer_id;
    int shipment_id;
};
struct shipment {
    int package_id;
    int cust_id_from;
    int receiver_id;
    int delivery_status_code;
    int w;
    int type;
    string timeline;
    int cost;
    int prepaid;
    string ordered_at;
    string delivered_at;
    int dest_addr_id;
};
struct delivery_log {
    int _id;
    int package_id;
    int location_id;
    int transportation_id;
    int delivery_status_code;
    string starting_time;
    int cost_incurred;
};


vector<string>statusList = {"ordered", "on the way", "returned", "delivered", "cancelled", "delivery error", "no payment return"};
vector<string> packageTypeList = {"heavy", "massive", "small", "breakable", "high" , "large", "great", "glass", "expensive"};
vector<deliveryStatus> ds(7);
vector<packageType> ps(9);
vector<address> as(noAdd);
vector<shipment> ss(ships);
vector<receiver> res(mx);
vector<transaction> trs(ships);
vector<user> us(mx);
vector<delivery_log> dls(ships);
vector<Transport> ts(transport_mx);
void createTransportData() {
    for (int i=0;i<transport_mx;i++) {
        ts[i]._id = rand()%rndi;
        ts[i].identification_code = rand()%rndi;
        ts[i].cost_per_km = rand()%30;
        ts[i].type = "t_" + to_string(rand()%transport_mx);
        ts[i].model_no = rand()%rndi;
    }
}
string createTransportQuery() {
    string query = "INSERT INTO `transportation`(`_id`, `type`, `cost_per_km`, `identification_code`, `model_no`) VALUES\n";
    for(int i=0;i<transport_mx;i++) {
        query += ("(" + to_string(ts[i]._id) + ",'" + ts[i].type + "'," + to_string(ts[i].cost_per_km) + "," + to_string(ts[i].identification_code) + "," + to_string(ts[i].model_no) + "),\n");
    }
    return query;
}

void createDeliveryStatus() {
    for(int i=1;i<=7;i++) {
        ds[i-1].details = "akjlkkjdlakdj";
        ds[i-1].status = statusList[i-1];
        ds[i-1]._id = i;
    }
}
string createDeliveryQuery() {
    string query = "INSERT INTO `deliverystatus`(`_id`, `status`, `details`) VALUES\n";
    for(int i=0;i<7;i++) {
        query+=("(" +  to_string(ds[i]._id) + ",'" + ds[i].status + "','" + ds[i].details + "'),\n");
    }
    return query;
}

void createPackageTypeData() {
    for(int i=0;i<9;i++) {
        ps[i]._id = i+1;
        ps[i].details = "ahldflhaiudfh";
        ps[i].type = packageTypeList[i];
    }
}

string createPackageTypeQuery() {
    string query = "INSERT INTO `packagetype`(`_id`, `type`, `details`) VALUES \n";
    for(int i=0;i<9;i++) {
        query += ("(" + to_string(ps[i]._id) + ",'" + ps[i].type + "','" + ps[i].details + "'),\n");
    }
    return query;
}
void createAddressData() {
    set<int> s;
    int i= 0 ;
    while(i < noAdd) {
        as[i]._id = rand()%rndi;
        as[i].address = rs(1 + rand()%10);
        as[i].city = rs(1 + rand()%10);
        as[i].country = rs(1 + rand()%10);
        as[i].pincode = rs(1 + rand()%10);
        as[i].state = rs(1 + rand()%10);;
        as[i].locality = rs(1 + rand()%10);
        if (s.find(as[i]._id) == s.end()) {
            s.insert(as[i]._id);
            i++;
        }
    } 
}
string createAddressQuery() {
    string query = "INSERT INTO `addresses`(`_id`, `address`, `locality`, `city`, `state`, `pincode`, `country`) VALUES \n";
    for(int i=0;i<noAdd;i++) {
        query += "(" + to_string(as[i]._id) + ",'" + as[i].address + "','" + as[i].locality + "','" + as[i].city + "','" + as[i].state + "','" + as[i].pincode + "','" + as[i].country + "'),\n";
    }
    return query;
}
void createUserData() {
    set<pair<int,int>> s;
    int i = 0;

    while(i<mx) {
        us[i]._id = rand()%rndi;
        us[i].total_spent = rand()%rndi;
        us[i].registered_date = rd();
        us[i].registered = rand()%2;
        us[i].address_id = as[rand()%noAdd]._id;
        us[i].creditcard = rp();
        us[i].debts = rand()%1000;
        us[i].email = rs(10);
        us[i].firstName = firstNames[(rand()%(firstNames.size()))];
        us[i].lastName = lastNames[(rand()%(lastNames.size()))];
        us[i].phone = rp();
        if (s.find({us[i]._id, us[i].address_id}) == s.end()) {
            s.insert({us[i]._id, us[i].address_id});
            i++;
        }
    }
}
string createUserQuery() {
    string query = "INSERT INTO `users`(`_id`, `FirstName`, `LastName`, `Address_id`, `Debts`, `Phone`, `Email`, `Registered_at`, `Credit_card_number`, `total_spent`, `registered`) VALUES\n";
    for(int i=0;i<mx;i++) {
        query += "(" + to_string(us[i]._id) + ",'" + us[i].firstName + "','" + us[i].lastName + "'," + to_string(us[i].address_id) + "," + to_string(us[i].debts) + ",'" + us[i].phone + "','" + us[i].email + "','" + us[i].registered_date + "','" + us[i].creditcard + "'," + to_string(us[i].total_spent) + "," + to_string(us[i].registered) + "),\n";
    }
    return query;
}
void createReceiverData() {
    map<pair<int,int> ,int> mp;
    int i = 0;
    while(i<mx) {
        res[i].address_id = as[rand()%noAdd]._id;
        res[i]._id = rand()%rndi;
        res[i].name = firstNames[(rand()%(firstNames.size()))];
        res[i].phone = rp();
        res[i].registered = rand()%2;
        if (!mp[{res[i]._id, res[i].address_id}]) {
            mp[{us[i]._id, us[i].address_id}] = 1;
            i++;
        }
}
}
string createReceiverQuery() {
    string query = "INSERT INTO `receivers`(`_id`, `address_id`, `name`, `phone_number`, `registered`) VALUES\n";
    for(int i=0;i<mx;i++) {
        query += ("(" + to_string(res[i]._id) + "," + to_string(res[i].address_id) + ",'" + res[i].name + "','" + res[i].phone + "'," + to_string(res[i].registered)  + "),\n");
    }
    return query;
}
void createShipmentData() {
    map<int, int> mp;
    
    int i = 0;
    while(i<ships) {
        ss[i].package_id = rand()%rndi;
        ss[i].cost = rand()%1000;
        ss[i].cust_id_from = us[rand()%us.size()]._id;
        ss[i].delivered_at = rd();
        ss[i].delivery_status_code = ds[rand()%(ds.size())]._id;
        ss[i].dest_addr_id = as[rand()%noAdd]._id;
        ss[i].ordered_at = rd();
        ss[i].prepaid = rand()%2;
        ss[i].receiver_id = res[rand()%(res.size())]._id;
        ss[i].timeline = rd();
        ss[i].type = ps[rand()%(ps.size())]._id;
        ss[i].w = rand()%100;
        if (!mp[ss[i].package_id])  {
            mp[ss[i].package_id] = 1;
            i++;
        }
    }
}

string createShipmentQuery() {
    string query = "INSERT INTO `shipment`(`package_id`, `cust_id_from`, `receiver_id`, `delivery_status_code`, `package_weight`, `package_type`, `timeline`, `cost`, `prepaid`, `ordered_at`, `delivered_at`, `destination_address_id`) VALUES\n";
    for (int i=0;i<ships;i++) {
        query += "(" + to_string(ss[i].package_id) + "," + to_string(ss[i].cust_id_from) + "," + to_string(ss[i].receiver_id) + "," + to_string(ss[i].delivery_status_code) + "," + to_string(ss[i].w) + "," + to_string(ss[i].type) + ",'" + ss[i].timeline + "'," + to_string(ss[i].cost) + "," + to_string(ss[i].prepaid) + ",'" + ss[i].ordered_at + "','" +  ss[i].delivered_at + "'," + to_string(ss[i].dest_addr_id) + "),\n"; 
    }
    return query;
}

void createTransactionData() {
    map<int,int> mp;
    int i = 0;
    while(i < ships) {
        trs[i]._id = rand()%rndi;
        trs[i].shipment_id = ss[rand()%(ss.size())].package_id;
        trs[i].customer_id = us[rand()%(us.size())]._id;
        if (!mp[trs[i]._id])  {
            mp[trs[i]._id] = 1;
            i++;
        }
    }
}

string createTransactionQuery() {
    string query = "INSERT INTO `transactions`(`_id`, `customer_id`, `shipment_id`) VALUES\n";
    for(int i=0;i<ships;i++) {
        query += "(" + to_string(trs[i]._id) + "," + to_string(trs[i].customer_id) + "," + to_string(trs[i].shipment_id) +  "),\n";
    }
    return query;
}

void createDeliveryInfoData() {
    map<int,int> mp;
    int i =0 ;
    while(i < ships) {
        dls[i]._id  = rand()%rndi;
        dls[i].transportation_id = ts[rand()%(ts.size())]._id;
        dls[i].starting_time = rd();
        dls[i].package_id = ss[rand()%(ss.size())].package_id;
        dls[i].location_id = as[rand()%(as.size())]._id;
        dls[i].delivery_status_code = ds[rand()%(ds.size())]._id;
        dls[i].cost_incurred = rand()%10000;
        if (!mp[dls[i]._id]) {
            mp[dls[i]._id] = 1;
            i++;
        }
    } 
}
string createDeliveryInfoQuery() {
    string query = "INSERT INTO `deliverylogs`(`_id`, `package_id`, `location_id`, `transportation_id`, `delivery_status_code`, `starting_time`, `cost_incurred`) VALUES\n";
    for(int i=0;i<ships;i++) {
        query += "(" + to_string(dls[i]._id) + "," + to_string(dls[i].package_id) + "," + to_string(dls[i].location_id) + "," + to_string(dls[i].transportation_id) + "," + to_string(dls[i].delivery_status_code) + ",'" + dls[i].starting_time + "',"+ to_string(dls[i].cost_incurred) + "),\n";
    }
    return query;
}
void ofw(ofstream* f, string data, string filename) {
    (*f).open(filename);
    (*f)<<data;
    (*f).close();
}
int main() {
    cout<<"RUnning";
    srand(time(0));
    createAddressData();
    createPackageTypeData();
    createTransportData();
    createDeliveryStatus();
    createUserData();
    createReceiverData();
    createShipmentData();
    createTransactionData();
    createDeliveryInfoData();
    cout<<"Still running";
    ofstream deliveryStatus, address, packageType, transport, user, receiver, shipment, transaction, deliveryInfo;
    cout<<"YEs";
    ofw(&deliveryStatus, createDeliveryQuery(), "delivery-status.txt");
    ofw(&address, createAddressQuery(), "addresses.txt");
    ofw(&packageType, createPackageTypeQuery(), "package-type.txt");
    ofw(&transport, createTransportQuery(), "transport.txt");
    ofw(&user, createUserQuery(), "user.txt");
    ofw(&receiver, createReceiverQuery(), "receiver.txt");
    ofw(&shipment, createShipmentQuery(), "shipment.txt");
    ofw(&transaction, createTransactionQuery(), "transaction.txt");
    ofw(&deliveryInfo, createDeliveryInfoQuery(), "delivery-info.txt");

}