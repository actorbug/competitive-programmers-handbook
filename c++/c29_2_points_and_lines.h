#pragma once

using P = complex<long double>;

long double inner_product(P a, P b);
long double cross_product(P a, P b);
long double point_location(P s1, P s2, P p);
bool point_inside_a_polygon(const vector<P>& p, P a);