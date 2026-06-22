class Solution
{
public:
    int activitySelection(vector<int> &start, vector<int> &finish)
    {
        vector<tuple<int, int>> meetings;
        for (int i = 0; i < start.size(); i++)
        {
            meetings.push_back({finish[i], start[i]});
        }
        sort(meetings.begin(), meetings.end());

        int lastEnd = -1;
        int count = 0;

        for (auto &m : meetings)
        {
            int e = get<0>(m);
            int s = get<1>(m);
            if (s > lastEnd)
            {
                lastEnd = e;
                count++;
            }
        }

        return count;
    }
};