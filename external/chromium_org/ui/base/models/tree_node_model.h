// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_BASE_MODELS_TREE_NODE_MODEL_H_
#define UI_BASE_MODELS_TREE_NODE_MODEL_H_

#include <algorithm>
#include <vector>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/logging.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "base/observer_list.h"
#include "base/strings/string16.h"
#include "ui/base/models/tree_model.h"

namespace ui {



template <class NodeType>
class TreeNode : public TreeModelNode {
 public:
  TreeNode() : parent_(NULL) {}

  explicit TreeNode(const base::string16& title)
      : title_(title), parent_(NULL) {}

  virtual ~TreeNode() {}

  
  virtual void Add(NodeType* node, int index) {
    DCHECK(node);
    DCHECK_GE(index, 0);
    DCHECK_LE(index, child_count());
    
    NodeType* parent = node->parent_;
    if (parent)
      parent->Remove(node);
    node->parent_ = static_cast<NodeType*>(this);
    children_.insert(children_.begin() + index, node);
  }

  
  
  virtual NodeType* Remove(NodeType* node) {
    typename std::vector<NodeType*>::iterator i =
        std::find(children_.begin(), children_.end(), node);
    DCHECK(i != children_.end());
    node->parent_ = NULL;
    children_.weak_erase(i);
    return node;
  }

  
  void RemoveAll() {
    for (size_t i = 0; i < children_.size(); ++i)
      children_[i]->parent_ = NULL;
    children_.weak_clear();
  }

  
  
  void SetChildren(const std::vector<NodeType*>& children) {
    RemoveAll();
    for (size_t i = 0; i < children.size(); ++i)
      Add(children[i], i);
  }

  
  const NodeType* parent() const { return parent_; }
  NodeType* parent() { return parent_; }

  
  bool is_root() const { return parent_ == NULL; }

  
  int child_count() const { return static_cast<int>(children_.size()); }

  
  bool empty() const { return children_.empty(); }

  
  
  int GetTotalNodeCount() const {
    int count = 1;  
    for (size_t i = 0; i < children_.size(); ++i)
      count += children_[i]->GetTotalNodeCount();
    return count;
  }

  
  const NodeType* GetChild(int index) const {
    DCHECK_GE(index, 0);
    DCHECK_LT(index, child_count());
    return children_[index];
  }
  NodeType* GetChild(int index) {
    return const_cast<NodeType*>(
        static_cast<const NodeType&>(*this).GetChild(index));
  }

  
  int GetIndexOf(const NodeType* node) const {
    DCHECK(node);
    typename std::vector<NodeType*>::const_iterator i =
        std::find(children_.begin(), children_.end(), node);
    return i != children_.end() ? static_cast<int>(i - children_.begin()) : -1;
  }

  
  virtual void SetTitle(const base::string16& title) { title_ = title; }

  
  virtual const base::string16& GetTitle() const OVERRIDE { return title_; }

  
  
  bool HasAncestor(const NodeType* ancestor) const {
    if (ancestor == this)
      return true;
    if (!ancestor)
      return false;
    return parent_ ? parent_->HasAncestor(ancestor) : false;
  }

 protected:
  std::vector<NodeType*>& children() { return children_.get(); }

 private:
  
  base::string16 title_;

  
  NodeType* parent_;

  
  ScopedVector<NodeType> children_;

  DISALLOW_COPY_AND_ASSIGN(TreeNode);
};


template <class ValueType>
class TreeNodeWithValue : public TreeNode< TreeNodeWithValue<ValueType> > {
 public:
  TreeNodeWithValue() {}

  explicit TreeNodeWithValue(const ValueType& value)
      : ParentType(base::string16()), value(value) {}

  TreeNodeWithValue(const base::string16& title, const ValueType& value)
      : ParentType(title), value(value) {}

  ValueType value;

 private:
  typedef TreeNode< TreeNodeWithValue<ValueType> > ParentType;

  DISALLOW_COPY_AND_ASSIGN(TreeNodeWithValue);
};


template <class NodeType>
class TreeNodeModel : public TreeModel {
 public:
  
  
  explicit TreeNodeModel(NodeType* root) : root_(root) {}
  virtual ~TreeNodeModel() {}

  NodeType* AsNode(TreeModelNode* model_node) {
    return static_cast<NodeType*>(model_node);
  }

  void Add(NodeType* parent, NodeType* node, int index) {
    DCHECK(parent && node);
    parent->Add(node, index);
    NotifyObserverTreeNodesAdded(parent, index, 1);
  }

  NodeType* Remove(NodeType* parent, NodeType* node) {
    DCHECK(parent);
    int index = parent->GetIndexOf(node);
    NodeType* delete_node = parent->Remove(node);
    NotifyObserverTreeNodesRemoved(parent, index, 1);
    return delete_node;
  }

  void NotifyObserverTreeNodesAdded(NodeType* parent, int start, int count) {
    FOR_EACH_OBSERVER(TreeModelObserver,
                      observer_list_,
                      TreeNodesAdded(this, parent, start, count));
  }

  void NotifyObserverTreeNodesRemoved(NodeType* parent, int start, int count) {
    FOR_EACH_OBSERVER(TreeModelObserver,
                      observer_list_,
                      TreeNodesRemoved(this, parent, start, count));
  }

  void NotifyObserverTreeNodeChanged(TreeModelNode* node) {
    FOR_EACH_OBSERVER(TreeModelObserver,
                      observer_list_,
                      TreeNodeChanged(this, node));
  }

  
  virtual NodeType* GetRoot() OVERRIDE {
    return root_.get();
  }

  virtual int GetChildCount(TreeModelNode* parent) OVERRIDE {
    DCHECK(parent);
    return AsNode(parent)->child_count();
  }

  virtual NodeType* GetChild(TreeModelNode* parent, int index) OVERRIDE {
    DCHECK(parent);
    return AsNode(parent)->GetChild(index);
  }

  virtual int GetIndexOf(TreeModelNode* parent, TreeModelNode* child) OVERRIDE {
    DCHECK(parent);
    return AsNode(parent)->GetIndexOf(AsNode(child));
  }

  virtual TreeModelNode* GetParent(TreeModelNode* node) OVERRIDE {
    DCHECK(node);
    return AsNode(node)->parent();
  }

  virtual void AddObserver(TreeModelObserver* observer) OVERRIDE {
    observer_list_.AddObserver(observer);
  }

  virtual void RemoveObserver(TreeModelObserver* observer) OVERRIDE {
    observer_list_.RemoveObserver(observer);
  }

  virtual void SetTitle(TreeModelNode* node,
                        const base::string16& title) OVERRIDE {
    DCHECK(node);
    AsNode(node)->SetTitle(title);
    NotifyObserverTreeNodeChanged(node);
  }

 private:
  
  ObserverList<TreeModelObserver> observer_list_;

  
  scoped_ptr<NodeType> root_;

  DISALLOW_COPY_AND_ASSIGN(TreeNodeModel);
};

}  

#endif  