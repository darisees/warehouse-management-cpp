# Warehouse Management System (C++)

This program is a simple warehouse management system implemented in C++.  
The main focus of this project is to apply **Data Structure concepts**, including:

- Circular Linked List  
- Single Linked List  
- Double Linked List  

This project was developed as part of the **Data Structures and Algorithms** course.

---

## 📌 Main Features

### 1. Item Management
- Add items to the warehouse  
- Automatically classify items based on weight:
  - Light (≤ 5 kg)
  - Heavy (> 5 kg)
- Storage system:
  - Light items → stored at the front (head)
  - Heavy items → stored at the back (tail)

---

### 2. Inspector System (Circular Linked List)
- Inspectors are managed in a circular rotation  
- Every 3 items processed → inspector rotates automatically  
- Tracks the number of items handled by each inspector  
- Displays statistics and the most productive inspector  

---

### 3. Item History (Single Linked List)
- Stores all processed items  
- Display full history  
- Filter history by:
  - Inspector name  
  - Item category  

---

### 4. Warehouse Storage (Double Linked List)
- Dynamically stores items  
- Displays complete warehouse data:
  - Item name  
  - Weight  
  - Category  
  - Inspector  
- Delete items based on category  

---

## ⚙️ Data Structure Concepts

| Data Structure         | Purpose                  |
|-----------------------|--------------------------|
| Circular Linked List  | Inspector rotation       |
| Single Linked List    | Item history             |
| Double Linked List    | Warehouse storage        |
