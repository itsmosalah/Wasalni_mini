#pragma once


class edge {
public:
    int from, to, distance;
    bool operator < (edge x) const;
};