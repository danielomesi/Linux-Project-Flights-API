# Flight Data Service (Containerized)

**Experience the power of real-time flight data with Flight Data Service, now fully containerized for seamless deployment and execution! This application provides an efficient and robust solution for accessing and displaying flight information for airports and aircrafts. This project utilizes a client/server architecture, with the two components running in separate Docker containers for enhanced isolation and portability.**

## Project Overview

Flight Data Service leverages a two-container design to deliver a powerful flight information experience:

*   **`dbService` Container:** This container houses the data-handling server, responsible for retrieving, storing, and managing flight data.
*   **`flightsService` Container:** This container provides the user interface, enabling you to interact with the system and query flight information through a command-line interface.

The containers communicate through named pipes, ensuring a clean separation of concerns and efficient data transfer.

## Key Features

*   **Dockerized:**  Runs entirely within Docker containers for easy deployment and dependency management.
*   **Client/Server Architecture:** The `dbService` and `flightsService` containers work in tandem.
*   **Named Pipe IPC:** Robust inter-process communication using named pipes within the container environment.
*   **Command-Line Interface:** User-friendly CLI for interacting with flight data within the `flightsService` container.
*   **Airport Data:** Fetch and display data for specific airports, including full schedule and arrivals.
*   **Aircraft Data:** Fetch and display data for specific aircrafts, including full schedule.
* **Zip DB:** Database is zipped at each execution.

## Getting Started (Docker)

Follow these steps to get Flight Data Service up and running on your system using Docker:

1.  **Prerequisites:**
    *   Docker and Docker Compose installed on your machine.
    *   The `Ex03.zip` file.

2.  **Setup:**
    *   Extract the contents of `Ex03.zip` to a folder named `program` on your local machine.
    *   The `program` folder should now contain: `runDBService.sh` and `runFlightsService.sh`.

3.  **Permissions:**
    *   Open a terminal and navigate to the `program` directory: `cd program`
    *   Make the shell scripts executable: `chmod u+x runDBService.sh runFlightsService.sh`

4.  **Start the `dbService` Container:**
    *   In the same terminal, run the `dbService` container: `./runDBService.sh`
    * This will start the `dbService` container in detached mode.
    *   This will run the dbService on a docker container.

5.  **Start the `flightsService` Container:**
    *   Open a **new terminal** and navigate to the `program` directory: `cd program`
    *   Run the `flightsService` container: `./runFlightsService.sh`
    * This will run the flightsService on a docker container.

6.  **Interact with `flightsService`:**
    *   You will now be inside the `flightsService` container at the `/home/program/` directory.
    *   Set the library path: `export LD_LIBRARY_PATH=.`
    *   Run the application: `./flightsService`
    *   Follow the on-screen prompts in the CLI to interact with the flight data.

## Important Notes

*   **Exiting the Application:** When you choose the 'Exit' (option 6) operation in the `flightsService` CLI, the `dbService` container will automatically stop, while the `flightsService` container will keep running. This is specified in the project instructions.
*   **Restarting the Application:** If you wish to run the program again after exiting, you must manually restart the `dbService` container by running `./runDBService.sh` again. Then, you can re-enter the `flightsService` container and re-execute the `./flightsService` command.

## Project Team

*   Daniel Omesi, ID 207689092
*   Ido Beit On, ID 208538488
*   Sara Benita, ID 209297225

## Contributing

Contributions are welcome! Please read the `CONTRIBUTING.md` file for details.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.
