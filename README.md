# OdelTouring

## Build

### Requirements
- CMake ≥ 3.30
- A compiler with C++ modules and C++23 (`std::expected`) support — recent GCC / Clang / MSVC; a Ninja or Visual Studio generator is needed for modules
- Internet access on the first configure: [nlohmann/json](https://github.com/nlohmann/json) 3.11.3 is downloaded automatically via `FetchContent`

### Steps

```bash
git clone <url>
cd OdelTouring
cmake -B build -S . -G Ninja
cmake --build build
./build/odelTouring
```

### CMake options

| Option | Default | Description |
|---|---|---|
| `TEST_INTERFACE` | `OFF` | Builds the `test` executable (from `test.cpp`) instead of `odelTouring`, to try the new interface |
| `USE_SANITIZERS` | `OFF` | With `TEST_INTERFACE=ON`: enables AddressSanitizer and UBSan for `test` |

> **Note:** C++ named modules support varies across compiler and CMake versions. The latest versions are strongly recommended.

---

## About

**OdelTouring** is a console application for keeping records of tours and customers in a travel agency. It stores managers, customers, trips and orders; lets managers sell and return trips on behalf of customers; and provides analytics on sold trips.

### Features

- **Managers** — add, view, edit, remove; sell and return trips on behalf of customers
- **Customers** — client records with address, phone number and purchase counter; status tracking (no trip / trip booked / currently travelling)
- **Trips** — tours with country, city, dates and price (max duration: 60 days); automatic status (on sale / sold / in progress / finished / expired)
- **Orders** — an order is created when a trip is sold and removed when the sale is returned
- **Analytics** — number of orders, average price and duration, most popular countries (for a chosen year or for all time)
- **Logging** — user actions are appended to `History.txt`
- **JSON persistence** — data is loaded on startup and saved on exit

---

## Tech Stack

- **Language:** C++20 as the foundation — **modules** (named modules and partitions) and **coroutines** (terminal menus) — plus C++23 for `std::expected` (error reporting of sale/return operations)
- **Build system:** CMake 3.30+
- **Libraries:** [nlohmann/json](https://github.com/nlohmann/json) 3.11.3 (data persistence)

---

## User Interface

The terminal UI is implemented with **C++20 coroutines**: every menu is a `MenuItem` coroutine, and menus switch between each other through `MenuItemsHandles` (a set of coroutine handles). `main.cpp` creates all menus, stores their handles, loads data and resumes `main_menu`.

```
Main
├── Managers
│   ├── Information  → show full info · edit
│   ├── Add new manager
│   └── Remove manager
├── Customers
│   ├── Information  → show full info · edit · (list by trip country)
│   ├── Add new customer
│   └── Remove customer
├── Trips
│   ├── Information  → show full info · edit · general info
│   ├── Add new trip
│   └── Remove trip
└── Orders
    ├── Information  → general · for a specific year
    ├── Make an order
    └── Make an order return
```

Every submenu also offers *Back*, *Go to Main menu* and *Close the program*.

---

## Project Structure

```
.
├── CMakeLists.txt
├── main.cpp                    # Entry point: build menus → read data → run UI → save data
│
├── Person.cppm                 # Module Person: abstract base class (name, phone, ID, validation)
├── Order.cppm                  # Module Order: struct Order (record of a sold trip)
│
├── CustomerManagerTrip.cppm    # Primary interface: re-exports partitions below
├── Customer.cppm / Customer.cpp   # partition :Customer — class Customer (: Person)
├── Manager.cppm  / Manager.cpp    # partition :Manager  — class Manager (: Person); sale/return logic
├── Trip.cppm     / Trip.cpp       # partition :Trip     — class Trip, TripStatus, date helpers
│
├── Functions.cppm              # Primary interface: re-exports :Interface and :QueryFunctions
├── Interface.cppm / Interface.cpp           # partition :Interface — terminal UI (coroutine menus)
└── QueryFunctions.cppm / QueryFunctions.cpp # partition :QueryFunctions — queries, JSON I/O, logging
```

### Module Dependency Graph

```
Person ──┐
         ├──> CustomerManagerTrip (:Customer, :Manager, :Trip) ──┐
Order ───┘                                                       ├──> Functions (:Interface, :QueryFunctions) ──> main
Order ───────────────────────────────────────────────────────────┘
```

CMake targets: `Person`, `Order`, `CustomerManagerTrip`, `Functions` (static libraries with `CXX_MODULES` file sets) and the executable `odelTouring`.

---

## Data Models

### Person *(abstract)*
| Field | Type | Description |
|---|---|---|
| `second_name`, `first_name`, `patronymic_name` | `string` | Full name (entered as `Surname Name Patronymic`) |
| `phone_number` | `string` | Format `+380XXXXXXXXX`; must be unique across all people |
| `personal_id` | `int` | Unique ID (auto-generated if not given) |

Phone validation is done in `Person::SetPhoneNumber` (length, `+380` prefix, digits only, uniqueness); invalid input is re-requested from the user.

### Customer *(: Person)*
| Field | Type | Description |
|---|---|---|
| `address` | `string` | Home address |
| `count_of_bought_trips` | `int` | Total number of trips purchased |
| `trip` | `shared_ptr<Trip>` | Current trip (or `nullptr`) |
| `name_of_manager` | `string` | Manager who handled the current trip |

**Customer statuses:** `WITHOUT_TRIP` · `WITH_TRIP` (trip not started yet) · `DURING_A_TRIP`
(a customer whose trip is `FINISHED` is treated as `WITHOUT_TRIP`).

### Manager *(: Person)*
Operations (`Manager` is a friend of `Customer` and `Trip`, so only it can change their purchase state):
- `SaleTheTrip(customer, trip)` → `std::expected<std::shared_ptr<Order>, const char*>` — sells a trip; fails if the trip or the customer already has a purchase
- `ReturnTheTrip(customer)` → `std::expected<bool, const char*>` — returns a trip; fails if the customer has no trip or the trip has already started

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

**Trip statuses** (computed from today's date and the booking date):
`ON_SALE` · `SOLD` · `IN_PROGRESS` · `FINISHED` · `EXPIRED`

Static helpers `Trip::GetAveragePrice()` / `Trip::GetAverageDuration()` give statistics over all existing trips.

### Order
Created by `Manager::SaleTheTrip`.

| Field | Type |
|---|---|
| `name_of_trip` | `string` |
| `year_of_booking` | `int` |
| `country` | `string` |
| `duration` | `size_t` |
| `price` | `double` |
| `customer_id` | `size_t` |

---

## Data Files

| File | Format | Purpose |
|---|---|---|
| `Managers.json` | JSON | Manager records |
| `Customers.json` | JSON | Customer records (linked to trips by trip ID) |
| `Trips.json` | JSON | Trip records, including status and (for sold trips) booking data |
| `Orders.json` | JSON | Orders |
| `History.txt` | text | Timestamped action log (append-only) |

> Files are read on every startup (in the order managers → trips → customers → orders, because customers reference trips) and overwritten on exit.
> If a file is missing, an error message is printed and the program continues with an empty collection.

---

## Known Issues

- Exception safety and checking of function results are not complete in several places (see the note at the end of `main.cpp`).
- The "List of customers by trip country" menu (`ListOfCustomersByTripsCountryMenu`) is implemented but not yet created/connected in `main.cpp`.
- The `TEST_INTERFACE` branch is unfinished: `Functions.cppm` expects a `:NewInterface` partition, and the compile definition in `CMakeLists.txt` (`TEST_NEW_...`) is truncated.
- Some input validation is duplicated between `Person` and `Manager` (e.g. `SetPhoneNumber`, `SetFullName`).
