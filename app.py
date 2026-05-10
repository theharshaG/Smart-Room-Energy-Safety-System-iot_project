from flask import Flask, request, jsonify, render_template
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)

# DATABASE
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///room.db'
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False

DB = SQLAlchemy(app)

# MODEL
class Room(DB.Model):

    id = DB.Column(DB.Integer, primary_key=True)

    pir = DB.Column(DB.Integer)
    ir = DB.Column(DB.Integer)

    temperature = DB.Column(DB.Float)
    humidity = DB.Column(DB.Float)

with app.app_context():
    DB.create_all()

# HOME PAGE
@app.route("/")
def home():
    return render_template("index.html")

# RECEIVE DATA
@app.route("/data", methods=["POST"])
def receive():

    data = request.get_json()

    pir = data["pir"]
    ir = data["ir"]

    temp = data["temp"]
    hum = data["hum"]

    print("PIR:", pir)
    print("IR:", ir)
    print("TEMP:", temp)

    new = Room(
        pir=pir,
        ir=ir,
        temperature=temp,
        humidity=hum
    )

    DB.session.add(new)
    DB.session.commit()

    return jsonify({"message": "saved"})

# SEND DATA
@app.route("/data", methods=["GET"])
def get_data():

    data = Room.query.all()

    result = []

    for d in data:

        result.append({
            "pir": d.pir,
            "ir": d.ir,
            "temp": d.temperature,
            "hum": d.humidity
        })

    return jsonify(result)

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000, debug=True)
