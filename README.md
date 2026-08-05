# OdelTouring

A **C++20** console application for managing a travel agency. Tracks managers, customers, and trips; handles sales and returns; and provides analytics on bookings.

---

## Features

- **Managers** — add, edit, delete; sell and return trips on behalf of customers
- **Customers** — manage client records with address, phone number, and purchase history; track current status (no trip / trip booked / currently travelling)
- **Trips** — create tours with country, city, dates, and price; automatic status tracking (on sale / sold / in progress / finished / expired)
- **Orders** — completed trips are automatically archived to `Orders.txt`
- **Analytics** — most popular countries, average price and duration (per year or all-time)
- **Logging** — all actions are written to `History.txt` with timestamps
- **File-based persistence** — data is loaded on startup and saved on exit

---

## Project Structure

```
.
├── CMakeLists.txt
├── main.cpp                    # Entry point: read → interface → save
│
├── Person.cppm                 # Abstract base class Person (name, phone, ID)
│
├── CustomerManagerTrip.cppm    # Aggregate module: re-exports Customer, Manager, Trip
├── Customer.cppm               # Class Customer (extends Person)
├── Manager.cppm                # Class Manager (extends Person); sale/return logic
├── Trip.cppm                   # Class Trip; statuses, dates, price, analytics
│
├── Order.cppm                  # Struct Order (archived record of a completed trip)
│
├── Functions.cppm              # Aggregate module: re-exports Interface and QueryFunctions
├── Interface.cppm              # Terminal UI (menus, navigation, user interaction)
├── QueryFunctions.cppm         # Declarations of utility functions (I/O, queries)
└── QueryFunctions.cpp          # Implementation of utility functions
```

### Module Dependency Graph

```
Person
  └── CustomerManagerTrip (Customer, Manager, Trip)
        └── Order
              └── Functions (Interface, QueryFunctions)
                    └── main
```

---

## Data Models

### Person *(abstract)*
| Field | Type | Description |
|---|---|---|
| `second_name`, `first_name`, `patronymic_name` | `string` | Full name |
| `phone_number` | `string` | Phone in format `+380XXXXXXXXX` |
| `personal_id` | `int` | Unique ID (auto-generated) |

### Customer *(: Person)*
| Field | Type | Description |
|---|---|---|
| `address` | `string` | Home address |
| `count_of_bought_trips` | `int` | Total number of trips purchased |
| `trip` | `shared_ptr<Trip>` | Current trip (or `nullptr`) |
| `name_of_manager` | `string` | Manager who handled the current trip |

**Customer statuses:** `WITHOUT_TRIP` · `WITH_TRIP` · `DURING_A_TRIP`

### Manager *(: Person)*
Performs operations:
- `SaleTheTrip(customer, trip)` — sells a trip to a customer
- `ReturnTheTrip(customer)` — returns a trip (not allowed once the trip has started)

### Trip
| Field | Type | Description |
|---|---|---|
| `name` | `string` | Tour name |
| `country`, `city` | `string` | Destination |
| `date_of_start`, `date_of_end` | `year_month_day` | Tour dates (max duration: 60 days) |
| `price` | `double` | Price (UAH) |
| `personal_id` | `int` | Unique 7-digit ID |
| `name_of_customer`, `name_of_manager` | `string` | Set at the time of sale |
| `date_of_booking` | `year_month_day` | Date the trip was purchased |

**Trip statuses:** `ON_SALE` · `SOLD` · `IN_PROGRESS` · `FINISHED` · `EXPIRED`

### Order *(archive)*
Created automatically when a finished trip is saved.

| Field | Type |
|---|---|
| `year_of_booking` | `int` |
| `country`, `name_of_trip`, `name_of_customer` | `string` |
| `duration` | `int` |
| `price` | `double` |

---

## Data Files

| File | Purpose |
|---|---|
| `Managers.txt` | Manager records |
| `Customers.txt` | Customer records |
| `Trips.txt` | Active trip records |
| `Orders.txt` | Archive of completed orders |
| `History.txt` | Timestamped action log |

> Files are read on every startup and overwritten on exit.  
> Finished trips (`FINISHED`) are not kept in `Trips.txt` — they are moved to `Orders.txt`.

---

## Build

### Requirements
- CMake ≥ 3.30
- A compiler with **C++20 modules** support (GCC 14+ / Clang 17+ / MSVC 2022+)

### Steps

```bash
git clone <url>
cd OdelTouring
cmake -B build -S .
cmake --build build
./build/odelTouring
```

> **Note:** C++20 named modules (`import`) support varies across compiler and CMake versions. CMake 3.30+ with an up-to-date compiler is strongly recommended.

---

## Known Issues


- Exception safety and checking result of fuction are not yet complete in several places.
- The functionality for storing order history is not yet working.
---

## Tech Stack

- **Language:** C++20
- **Build system:** CMake 3.30
