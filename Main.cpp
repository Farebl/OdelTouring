#include "Functions.h" // <stack> + <algorithm> + <numeric> + <fstream> + Manager.h + Customer.h + Trip.h + Person.h +  <iostream> + <string> + <vector> + <list>

ListSharedsManager_t Managers; // ��������� ���������
ListSharedsCustomer_t Customers;// ��������� �볺���
ListSharedsTrip_t Trips;// ��������� ������

int main() {

	Start(Managers, Customers, Trips); // ������ ��������: ���������� �����, ���������, ���������� �����

	return 0;
}

/*
������ �� �������.
1.������ ���������. 
2.ʳ������ �볺���. 
3.������ �볺���, �� �������  ����� �����. 
4.������� ������� ������.
5.������� ��������� ������. 
6.�����, ��� �� ��������� �����.
*/
