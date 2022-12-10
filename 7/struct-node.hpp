//
// Created by zhongyang on 2022/12/7.
//

#ifndef INC_2022_STRUCT_NODE_HPP
#define INC_2022_STRUCT_NODE_HPP

#include <utility>
#include <unordered_map>
#include <string>

class Node
{
public:
    enum class Type : size_t
    {
        Dir = (1u << 0),
    };

protected:
    Type                                    m_type    = (Type) 0;
    size_t                                  m_size    = 0;
    Node                                    *m_parent = nullptr;
    std::unordered_map<std::string, Node *> m_children;
    std::string                             m_name;

public:
    bool IsDir() const
    {
        return ((size_t) m_type & (size_t) Type::Dir);
    }

    bool IsRoot() const
    {
        return this->m_parent == this;
    }

    size_t GetSize() const
    {
        if (!IsDir()) {
            return m_size;
        }

        size_t size_sum = 0;
        
        for (const auto &iter : m_children) {
            size_sum += iter.second->GetSize();
        }
        return size_sum;
    };

    Node *AddChild(Node *child)
    {
        if (child->m_parent != nullptr) {
            fprintf(stderr, "child %s has parent %s\n", child->m_name.c_str(), child->m_parent->m_name.c_str());
        }
        this->m_children[child->m_name] = child;
        child->m_parent = this;
        return this;
    }

    Node *GetParent() const
    {
        return this->m_parent;
    }

    Node *GetChild(const std::string &name) const
    {
        auto iter = this->m_children.find(name);
        if (iter == this->m_children.end()) {
            return nullptr;
        }
        return iter->second;
    }

    const std::string &GetName() const
    {
        return m_name;
    }

    void Walk(const std::function<void(const Node *)> &callback) const
    {
        callback(this);
        for (const auto &iter : m_children) {
            iter.second->Walk(callback);
        }
    }

    ~Node()
    {
        for (auto &n : m_children) {
            delete n.second;
            n.second = nullptr;
        }
        m_children.clear();
    }

    std::string Tree() const
    {
        std::string line;
        size_t      indent = 0;
        printNode(&line, &indent);
        return line;
    }

    static Node *NewFile(const std::string &name, size_t file_size)
    {
        return new Node(name, file_size);
    }

    static Node *NewDir(const std::string &name)
    {
        return new Node(name, Type::Dir);
    }

    static Node *NewRoot()
    {
        auto *root = NewDir("/");
        root->m_parent = root;
        return root;
    }

protected:
    void printNode(std::string *content, size_t *indent) const
    {
        char number[256];

        snprintf(number, 23, " (%zu)\n", GetSize());
        content->append((*indent) * 2, ' ').append("- ").append(m_name).append(number);
        ++(*indent);
        for (const auto &iter : m_children) {
            iter.second->printNode(content, indent);
        }
        --(*indent);
    }

    explicit Node(std::string name, size_t file_size)
            : m_name(std::move(name)), m_size(file_size)
    {
    }

    explicit Node(std::string name, Node::Type type)
            : m_name(std::move(name)), m_type(type)
    {
    }
};

#endif //INC_2022_STRUCT_NODE_HPP
