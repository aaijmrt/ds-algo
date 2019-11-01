bool check(ii p1, ii p, ii p2) {
    if((min(p1.X, p2.X) <=p.X) && (max(p1.X, p2.X) >= p.X) && (min(p1.Y, p2.Y) <= p.Y) && (max(p1.Y, p2.Y) >= p.Y))
        return true;
    return false;
}

ii point[lmt];
ll sum[lmt];

bool lineIntersection(ii p1, ii p2, ii p3, ii p4) {
    //1st line p1->p2, 2nd line p3->p4
    //Trying to make line of form Ax + By = C
    //This is only for integers. Change to double for real co-ordinates
    ll A1 = p2.Y - p1.Y, A2 = p4.Y - p3.Y;
    ll B1 = p1.X - p2.X, B2 = p3.X - p4.X;
    ll C1 = A1*p1.X + B1*p1.Y, C2 = A2*p3.X + B2*p3.Y;
    ll det = A1*B2 - A2*B1;
    if(det == 0)
        return false;
    ll X = (B2*C1 - B1*C2)/det;
    ll Y = (A1*C2 - A2*C1)/det;
    ii intersection = mp(X, Y);
    //DEB(X);
    //DEB(Y);
    if(check(p1, intersection, p2) && check(p3, intersection, p4))
        return true;
    return false; 
}