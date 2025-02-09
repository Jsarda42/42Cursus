-- CREATE DATABASE enzo;

-- USE enzo;

-- CREATE TABLE users (
--     id INT AUTO_INCREMENT PRIMARY KEY,
--     username VARCHAR(50) NOT NULL,
--     email VARCHAR(100) NOT NULL,
--     created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
-- );


DO $$ 
BEGIN 
    IF NOT EXISTS (SELECT FROM pg_database WHERE datname = 'yourdatabase') THEN
        CREATE DATABASE yourdatabase;
    END IF;
END $$;


DO $$ 
BEGIN 
    IF NOT EXISTS (SELECT FROM pg_catalog.pg_roles WHERE rolname = 'yourusername') THEN
        CREATE USER yourusername WITH PASSWORD 'yourpassword';
        ALTER ROLE yourusername SET client_encoding TO 'utf8';
        ALTER ROLE yourusername SET default_transaction_isolation TO 'read committed';
        ALTER ROLE yourusername SET timezone TO 'UTC';
    END IF;
END $$;

GRANT ALL PRIVILEGES ON DATABASE yourdatabase TO yourusername;
