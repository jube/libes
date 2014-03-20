# ChangeLog for `libes`

## `libes` 0.5

### 0.5.0 (29 Jan 2014)

* Add an overload for `registerHandler`
* Remove updateEntity from System (put it directly in LocalSystem and GlobalSystem)
* Add CustomSystem and SingleSystem

### 0.5.1 (19 Mar 2014)

* Add an option COMPILER_IS_NOT_CXX11_READY to improve some builds (thanks @SRombauts)
* Fix a little bug in `Store::remove` (thanks @SRombauts)
* Make ChangeLog consistent

### 0.5.2 (20 Mar 2014)

* Add suport for Travis CI
* Add a document about C++11 status for the project

## `libes` 0.4

### 0.4.0 (19 Dec 2013)

* Add an event system
* Remove Archetype
* The Manager now remembers the components of each entity

### 0.4.1 (18 Jan 2014)

* Add a hash function and a user-defined operator to define types

## `libes` 0.3

### 0.3.0 (27 Oct 2013)

* Change from unique_ptr to shared_ptr for systems in the Manager.
* Add local systems, i.e. systems that put entities in a grid
* Modified old systems into global systems

### 0.3.1 (27 Oct 2013)

* Add the release date in the ChangeLog

## `libes` 0.2

### 0.2.0 (11 Oct 2013)

* The Manager nows clearly gets the ownership of the systems
* There is now a template function for createStoreFor in the Manager

## `libes` 0.1

### 0.1.0 (18 Sep 2013)

* Initial version
