Here’s a **step-by-step “Patient” CRUD API tutorial** in a clean, beginner-friendly format. This will help you or anyone understand the standard Node.js/Express/PostgreSQL pattern for **controller → route → index.js → Postman (test)**.

---

# 🟩 Step-by-Step: Patient CRUD API Example

---

## 1️⃣ **Controller File: `patientController.js`**

Create a folder: `server/controllers/patientController.js`

```js
const pool = require("../db/connection");

// CREATE - Add new patient
exports.createPatient = async (req, res) => {
  const { user_id, first_name, last_name, gender, phone_no } = req.body;
  try {
    const result = await pool.query(
      `INSERT INTO patient (user_id, first_name, last_name, gender, phone_no)
       VALUES ($1, $2, $3, $4, $5) RETURNING *`,
      [user_id, first_name, last_name, gender, phone_no]
    );
    res.status(201).json(result.rows[0]);
  } catch (err) {
    console.error("Error adding patient:", err);
    res.status(500).send("Error adding patient");
  }
};

// READ - Get all patients
exports.getAllPatients = async (req, res) => {
  try {
    const result = await pool.query(`
      SELECT p.patient_id, p.first_name, p.last_name, p.gender, p.phone_no, u.email
      FROM patient p
      JOIN "user" u ON p.user_id = u.user_id
    `);
    res.json(result.rows);
  } catch (err) {
    console.error("Error fetching patients:", err);
    res.status(500).send("Error fetching patients");
  }
};

// UPDATE - Update a patient (PATCH for partial updates)
exports.updatePatient = async (req, res) => {
  const { patient_id } = req.params;
  const { first_name, last_name, gender, phone_no } = req.body;
  try {
    const result = await pool.query(
      `UPDATE patient
         SET first_name = COALESCE($1, first_name),
             last_name = COALESCE($2, last_name),
             gender = COALESCE($3, gender),
             phone_no = COALESCE($4, phone_no),
             updated_at = CURRENT_TIMESTAMP
       WHERE patient_id = $5
       RETURNING *`,
      [first_name, last_name, gender, phone_no, patient_id]
    );
    if (result.rowCount === 0) {
      return res.status(404).json({ error: "Patient not found" });
    }
    res.status(200).json(result.rows[0]);
  } catch (err) {
    console.error("Error updating patient:", err);
    res.status(500).send("Error updating patient");
  }
};

// DELETE - Remove a patient
exports.deletePatient = async (req, res) => {
  const { patient_id } = req.params;
  try {
    const result = await pool.query(
      `DELETE FROM patient WHERE patient_id = $1 RETURNING *`,
      [patient_id]
    );
    if (result.rowCount === 0) {
      return res.status(404).json({ error: "Patient not found" });
    }
    res.status(200).json({ message: "Patient deleted successfully" });
  } catch (err) {
    console.error("Error deleting patient:", err);
    res.status(500).send("Error deleting patient");
  }
};
```

---

## 2️⃣ **Route File: `patientRoutes.js`**

Create: `server/routes/patientRoutes.js`

```js
const express = require("express");
const router = express.Router();
const patientController = require("../controllers/patientController");

// GET all patients
router.get("/", patientController.getAllPatients);

// POST new patient
router.post("/", patientController.createPatient);

// PATCH (update) patient by id
router.patch("/:patient_id", patientController.updatePatient);

// DELETE patient by id
router.delete("/:patient_id", patientController.deletePatient);

module.exports = router;
```

---

## 3️⃣ **Update Main Server File: `index.js`**

**Your previous state:**
You already have all required `require` and `app.use` lines.
Just make sure this line is present:

```js
const patientRoutes = require("./routes/patientRoutes");
app.use("/api/patients", patientRoutes);
```

It can be anywhere with the other routes.

---

## 4️⃣ **How It All Flows**

1. **Request** (from Postman/client):

   * To `/api/patients`, with appropriate HTTP method and body.
2. **Route**:

   * `patientRoutes.js` matches the request path and method.
3. **Controller**:

   * The appropriate function (create, get, update, delete) is called.
4. **Database**:

   * Controller runs SQL on your PostgreSQL DB and returns result/error.

---

## 5️⃣ **Testing Each Endpoint in Postman**

### **A. Create Patient (POST)**

**POST** `http://localhost:5000/api/patients`
**Body:**

```json
{
  "user_id": 1,
  "first_name": "John",
  "last_name": "Smith",
  "gender": "male",
  "phone_no": "01711111111"
}
```

---

### **B. Get All Patients (GET)**

**GET** `http://localhost:5000/api/patients`
Returns array of all patients with their emails.

---

### **C. Update Patient (PATCH)**

**PATCH** `http://localhost:5000/api/patients/1`
**Body:**

```json
{
  "phone_no": "01822222222"
}
```

Returns updated patient data.

---

### **D. Delete Patient (DELETE)**

**DELETE** `http://localhost:5000/api/patients/1`
Deletes the patient with `patient_id = 1`.
Returns:

```json
{ "message": "Patient deleted successfully" }
```

---

## 6️⃣ **Conventional Best Practice**

* **Controller**: All DB logic, clean and modular.
* **Routes**: Only routes/method+path, nothing else.
* **index.js**: Only app setup and `.use()` for routers, nothing else.

---

## 7️⃣ **Directory Structure Example**

```
Pulse-Point-Doctor-Patient-Manangement-System/
├── server/
│   ├── controllers/
│   │   └── patientController.js
│   ├── routes/
│   │   └── patientRoutes.js
│   ├── db/
│   │   └── connection.js
│   └── index.js
```

---

## 8️⃣ **How to Add Another Table**

Just repeat the same pattern:

* `controllers/tableController.js`
* `routes/tableRoutes.js`
* Add line in `index.js`:

  ```js
  const tableRoutes = require("./routes/tableRoutes");
  app.use("/api/table", tableRoutes);
  ```

---
