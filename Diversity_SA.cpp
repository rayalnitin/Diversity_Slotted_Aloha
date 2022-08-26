#include <bits/stdc++.h>
#define pb push_back
using namespace std;

typedef pair<int, int> pii;

int main()
{

    int i, j, dist, x1, x2, y1, y2, r1, r2, nodes, n, m, mn, mx, x, y;
    cout << "\nEnter the dimensions of the maze(nxm):";
    cin >> n >> m;
    int ADJ[n][m];

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            ADJ[i][j] = ' '; // Initial configuration of the maze.
        }
    }
    cout << "\nEnter the min and max ranges of the nodes: ";
    cin >> mn >> mx;

    cout << "\nEnter the number of senders: ";
    cin >> nodes;

    srand(time(NULL));
    int copy;
    cout << "\nEnter no of instances: ";
    cin >> copy;
    int MATRIX[nodes][3 * copy];
    int counter = -2;

    for (i = 0; i < nodes; i++) // Randomly placing the ith sender in the maze.
    {
        for (int p = 0; p < copy; p++)
        {

            do
            {
                x = rand() % n;
                y = rand() % m;
            } while (ADJ[x][y] != ' '); // the position should be free.

            ADJ[x][y] = '*';
            MATRIX[i][counter + 2] = x;                       // x-coordinate
            MATRIX[i][counter + 3] = y;                       // y-coordinate
            MATRIX[i][counter + 4] = rand() % (mx - mn) + mn; // Random range.

            counter += 3;
        }
        counter = -2;
    }

    cout << "Placing the senders: \n";
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            cout << char(ADJ[i][j]); // Display the maze after randomly placing the senders.
        }
        cout << "\n";
    }

    map<int, int> mp;
    set<pii> points;
    int c1 = -2, c2 = -2;

    for (i = 0; i < nodes; i++)
    {
        for (int p = 0; p < copy; p++)
        {
            x1 = MATRIX[i][c1 + 2];
            y1 = MATRIX[i][c1 + 3];
            r1 = MATRIX[i][c1 + 4];

            for (j = i + 1; j < nodes; j++)
            {
                for (int q = 0; q < copy; q++)
                {
                    x2 = MATRIX[j][c2 + 2];
                    y2 = MATRIX[j][c2 + 3];
                    r2 = MATRIX[j][c2 + 4];
                    dist = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));

                    if (dist <= r1 && dist <= r2)
                    { // i and j can communicate, so adding them.
                        points.insert({x1, y1});
                        points.insert({x2, y2});
                        mp[i]++;
                        mp[j]++;
                    }

                    c2 += 3;
                }
                c2 = -2;
            }
            c1 += 3;
        }
        c1 = -2;
    }

    cout << "\nThe updated maze: " << endl;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            if (points.find({i, j}) != points.end())
            {
                cout << '*'; // Display the maze after randomly placing the senders.
            }
            else
                cout << " ";
        }
        cout << "\n";
    }
    cout << endl
         << "\nThe SENDERS who will participate are: ";
    for (auto &it : mp)
    {
        if (it.second > copy)
            it.second = it.second % copy + 1;
        cout << it.first + 1 << "[" << it.second << "]"
             << " ";
    }
    cout << endl;

    cout << "\n#########Using SLotted ALOHA#########\n";
    int Tp, Kmax;
    cout << "\nEnter Kmax: ";
    cin >> Kmax;
    cout << "\nEnter Tp: ";
    cin >> Tp;

    // Simulation
    vector<int> NODES;
    for (auto it : mp)
    {
        NODES.push_back(it.first + 1);
    }

    n = NODES.size();

    vector<int> Kvals(nodes + 1);
    vector<int> WaitTime(nodes +1);

    for (i = 0; i <= nodes; i++)
    {
        Kvals[i] = 0;
        WaitTime[i] = 0;
    }

    vector<int> TOSEND;

    int total = 0, slots, eff = 0;
    cout << "\nEnter the number of time slots to be used: ";
    cin >> slots;
    cout << endl;

    for (i = 0; i < slots; i++)
    {

        cout << "SLOT=" << i + 1 << endl;
        for (j = 0; j < n; j++)
        {
            // slot has been changed, Reducing the waiting times
            if (WaitTime[NODES[j]] > 0)
                WaitTime[NODES[j]]--;
        }

        TOSEND.clear();

        for (int k = 0; k < n; k++)
        {
            if (WaitTime[NODES[k]])
            {
                continue;
            }

            int node = NODES[k];
            if (rand() % 2)
            {
                TOSEND.pb(node);
            }
        }

        int sz = TOSEND.size();
        total += sz;

        if (sz > 1)
        {
            cout << "Collision occured!!!" << endl;

            for (int m = 0; m < sz; m++)
            { // increment the value of K for each node
                Kvals[TOSEND[m]]++;

                if (Kvals[TOSEND[m]] > Kmax)
                {
                    cout << "Aborting sender " << TOSEND[m] + 1 << "'s packet.\n";

                    Kvals[TOSEND[m]] = 0;
                    WaitTime[TOSEND[m]] = 0;
                }
                else
                {
                    cout << "Sender " << TOSEND[m] + 1 << " Blocked";
                    WaitTime[TOSEND[m]] = ((rand() % Kmax) + 1); // Random wait time.
                    cout << ". (waits for " << WaitTime[TOSEND[m]] << " time slots, K=" << Kvals[TOSEND[m]] << ")\n";
                    WaitTime[TOSEND[m]]++;
                }
            }
        }

        else if (sz == 1)
        {
            cout << "Sender " << TOSEND[0] + 1 << "'s packet successfully transmitted!\n";
            eff++;
            WaitTime[TOSEND[0]] = 0;
            Kvals[TOSEND[0]] = 0;
        }
        cout << endl;
    }
    cout << "\nTotal number of packets=" << total;
    cout << "\nTotal number of packets sent=" << eff << endl;
}